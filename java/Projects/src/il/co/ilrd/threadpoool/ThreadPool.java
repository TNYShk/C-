package il.co.ilrd.threadpoool;

import il.co.ilrd.waitablepriorityqueue.WaitablePriorityQueueSem;

import java.util.LinkedList;
import java.util.List;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadPool implements Executor {
    protected WaitablePriorityQueueSem<Task<?>> wpq;
    private int numOfThreadz;
    private static final int HIGH_AS_KITE = 100;
    private static final int LOW_LOW_LOW = -5;
    private final Semaphore stopLightSem;
    protected List<ThreadAction> deadpool;


    public ThreadPool(int numberOfThreads) {
        if (numberOfThreads <= 0)
           throw new IllegalArgumentException();

        numOfThreadz = numberOfThreads;
        stopLightSem = new Semaphore(0);
        wpq = new WaitablePriorityQueueSem<>(numOfThreadz);
         deadpool = new LinkedList<>();

        for(int i = 0; i<numOfThreadz;++i){
            deadpool.add(new ThreadAction());
        }

        for(ThreadAction begin : deadpool){
            begin.start();
        }
    }

    public enum Priority {
        LOW,
        MED,
        HIGH
    }

    private final Callable<Void> shutItDown = () -> {
        ThreadAction shalter = (ThreadAction) ThreadAction.currentThread();
        shalter.isRunning.set(false);

         return null;
    };

    public Future<Void> submit(Runnable task, Priority priority) throws InterruptedException {
       return this.submit( Executors.callable(task,null), priority);
    }

    public <T> Future<T> submit(Runnable task, Priority priority, T returnValue) throws InterruptedException {
       return this.submit(Executors.callable(task,returnValue),priority);
    }
    public <T> Future<T> submit(Callable<T> task) throws InterruptedException {
        return this.submit(task,Priority.MED);
    }
    public <T> Future<T> submit(Callable<T> task, Priority priority) throws InterruptedException {
       if(shutIt.get())
           throw new InterruptedException();
        Task<T> creaTask = new Task<>(task,priority);
        wpq.enqueue(creaTask);
        return creaTask.futureHolder;
    }

    @Override
    public void execute(Runnable run) {
        try {
            this.submit(run,Priority.MED);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void setNumberOfThreads(int updateNumberOfThreads) throws InterruptedException {
        int remainder = updateNumberOfThreads - numOfThreadz;

        if (remainder >= 0) {
            while (0 <= --remainder) {
                ThreadAction added = new ThreadAction();
                deadpool.add(added);
                added.start();
            }
        } else {
            remainder = -remainder;
            while (0 <= --remainder) {
                wpq.enqueue(new Task<>(shutItDown, HIGH_AS_KITE));
            }
        }
        numOfThreadz = updateNumberOfThreads;
    }
        /*

        idea2:
        submit new task to pq with pause/terminate thread/semaphore with HIGH priority
            if newNumofThreads > numberOfThreads

         */

    // numberOfTHreads > 0 // problem if numberOfThreads is less than in Ctor, (the number of threads will be decreased)

    public void pause() throws InterruptedException {
        Callable<Void> pauseIt = () ->{
            stopLightSem.acquire();
            return null;
        };
        for(int i =0; i<numOfThreadz;++i) {
            wpq.enqueue(new Task<>(pauseIt,HIGH_AS_KITE));
        }

    } // after pause threads wont take tasks from the queue

    public void resume() {
        stopLightSem.release(numOfThreadz);
    } // reverse pause operation
private AtomicBoolean shutIt = new AtomicBoolean(false);
    public void shutdown() throws InterruptedException {
        shutIt.set(true);
        for(int i =0; i<numOfThreadz;++i) {
            wpq.enqueue(new Task<>(shutItDown,LOW_LOW_LOW));

        }
        //while(!wpq.isEmpty());
        //deadpool.clear();
    }
        //create tasks as number of threads, with low priority and kill, thus all original tasks will be done and then all threads kill
     // after shutdown submit will throw exceptions, nothing will work. all current tasks in the queue will execute. not blocking

    public void awaitTermination() throws InterruptedException {
        this.awaitTermination(Long.MAX_VALUE,TimeUnit.DAYS);
    } // wait for all threads to finish?


    public void awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {

        for (ThreadAction t : deadpool) {
            t.join(unit.convert(timeout, unit));
        }
        deadpool.clear();
    }




    private class Task<T> implements Comparable<Task<?>> {
        //private Priority priority;
        private Integer realPriority;
        private final TaskFuture futureHolder;
        private Callable<T> gullible;
        private T result;
        private final AtomicBoolean doneFlag = new AtomicBoolean(false);

        public Task(Callable<T> gullible, Integer realPriority){
            this.realPriority = realPriority;
            this.gullible = gullible;
            futureHolder = new TaskFuture(this);
        }
        public TaskFuture getIt(){
            return futureHolder;
        }
        public Task(Callable<T> call, Priority priority) {
          this(call, priority.ordinal());
        }

        void execute() throws Exception {
           result = gullible.call();
           doneFlag.set(true);
           futureHolder.futureLock.lock();
           futureHolder.blockResult.signal();
           futureHolder.futureLock.unlock();
        }


        @Override
        public int compareTo(Task<?> task) {
            return task.realPriority.compareTo(this.realPriority);
        }
        private class TaskFuture implements Future<T>{
            private ReentrantLock futureLock = new ReentrantLock();
            private Condition blockResult = futureLock.newCondition();
            private AtomicBoolean status = new AtomicBoolean();
            private Task<T> holder;

            public TaskFuture(Task<T> newTask){
                holder = newTask;
            }

            @Override
            public boolean cancel(boolean b) {
                boolean trial = false;
                if(isCancelled()) {
                    return false;
                }
                try {
                    trial = wpq.remove(holder);

                    } catch (InterruptedException e) {
                      throw new RuntimeException(e);
                    }finally {
                        if(trial){
                            status.set(true);
                            doneFlag.set(true);
                        }
                    }
                return trial;
            }

            @Override
            public boolean isCancelled() {
                return status.get();
            }
            @Override
            public boolean isDone() {
               return doneFlag.get();
            }

            @Override
            public T get() throws InterruptedException {
                try {
                    return get(Long.MAX_VALUE,TimeUnit.DAYS);
                } catch (TimeoutException e) {
                    throw new RuntimeException(e);
                }
                /*futureLock.lock();
                    while(!isDone()){
                        blockResult.await();
                    }
                    futureLock.unlock();
                return result;*/
            }
            @Override
            public T get(long l, TimeUnit timeUnit) throws InterruptedException, TimeoutException {
                futureLock.lock();
                if(!isDone()){
                    blockResult.await(l,timeUnit);
                }
                futureLock.unlock();
                return result;
            }
        }
    }

    private class ThreadAction extends Thread {
    private final AtomicBoolean isRunning = new AtomicBoolean(true);
        @Override
        public void run(){
            while(isRunning.get()) {
                Task<?> toPerform;
                try {
                    toPerform = wpq.dequeue();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                try {
                    toPerform.execute();
                   /* toPerform.doneFlag.getAndSet(true);*/
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
            }
        }

    }
}
