package il.co.ilrd.threadpoool;

import il.co.ilrd.waitablepriorityqueue.WaitablePriorityQueueSem;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ThreadPool implements Executor {
    private final WaitablePriorityQueueSem<Task<?>> wpq;

    private final int NUM_OF_THREADS;
    private Semaphore runSem = new Semaphore(0);

    public ThreadPool(int numberOfThread) {
        if (numberOfThread == 0)
            numberOfThread = 11;

        NUM_OF_THREADS = numberOfThread;

        wpq = new WaitablePriorityQueueSem<>(NUM_OF_THREADS);
        List<ThreadAction> deadpool = new ArrayList<>(NUM_OF_THREADS);

        for(ThreadAction ignored : deadpool){
            deadpool.add(new ThreadAction());
        }
        for(ThreadAction thi: deadpool){
            thi.start();
        }

    }

    public enum Priority {
        LOW,
        MED,
        HIGH
    }

    public Future<Void> submit(Runnable task, Priority priority) throws InterruptedException {
       return this.submit( Executors.callable(task,null),priority);

    }

    public <T> Future<T> submit(Runnable task, Priority priority, T returnValue) throws InterruptedException {
       return this.submit(Executors.callable(task,returnValue),priority);
    }
    public <T> Future<T> submit(Callable<T> task) throws InterruptedException {
        return this.submit(task,Priority.MED);
    }
    public <T> Future<T> submit(Callable<T> task, Priority priority) throws InterruptedException {
        Task<T> creaTask = new Task<>(task,priority);
        wpq.enqueue(creaTask);
        return creaTask.anotherHolder;
    }


    @Override
    public void execute(Runnable run) {
        //calls submit with default priority, creates callable and submits it to the wpq
        try {
            this.submit(run,Priority.MED);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void setNumberOfThreads(int updateNumberOfThreads) {
        /*

        idea2:
        submit new task to pq with pause/terminate thread/semaphore with HIGH priority
            if newNumofThreads > numberOfThreads

         */

    } // numberOfTHreads > 0 // problem if numberOfThreads is less than in Ctor, (the number of threads will be decreased)

    public void pause() throws InterruptedException {
       //create task with high priority and sempahore.acquire (is zero thus thread is stuck)

    } // after pause threads wont take tasks from the queue

    public void resume() {
        //sem.release(numOfThreads)
    } // reverse pause operation

    public void shutdown() {
        //create tasks as number of threads, with low priority and kill, thus all original tasks will be done and then all threads kill
    } // after shutdown submit will throw exceptions, nothing will work. all current tasks in the queue will execute. not blocking

    public void awaitTermination() {
        // call this with time 0 this(0,unit);
    } // wait for all threads to finish?

    public void awaitTermination(long timeout, TimeUnit unit) {
    }


    private class Task<T> implements Comparable<Task<?>> {
        private Priority priority;
        private int realPriority ;
        private TaskFuture anotherHolder;
        private Callable<T> gullible;

        private T result;
        private AtomicBoolean doneFlag = new AtomicBoolean(false);

        public Task(Callable<T> call, Priority priority) {
            this.gullible = call;
            this.priority = priority;
            anotherHolder = new TaskFuture();
        }

        void execute() throws Exception {
           result = gullible.call();
        }

        @Override
        public int compareTo(Task<?> task) {
            return this.priority.compareTo(task.priority);

        }

        private class TaskFuture implements Future<T>{
            private Task<T> holder;
            public boolean cancel(){return true;}

            @Override
            public boolean cancel(boolean b) {
                return false;
            }
            @Override
            public boolean isCancelled() {
                return false;
            }
            @Override
            public boolean isDone() {

                return false;
            }

            @Override
            public T get() throws InterruptedException, ExecutionException {
                return result;

            }

            @Override
            public T get(long l, TimeUnit timeUnit) throws InterruptedException, ExecutionException, TimeoutException {
                return null;
            }
        }
    }

    private class ThreadAction extends Thread {
    private final AtomicBoolean isRunning = new AtomicBoolean(true);
   @Override
        public void run(){
            while(isRunning.get()) {
                Task<?> tt;
                try {
                    tt = wpq.dequeue();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                try {
                    tt.execute();
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }
}
