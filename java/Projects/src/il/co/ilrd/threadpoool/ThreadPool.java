package il.co.ilrd.threadpoool;

import il.co.ilrd.waitablepriorityqueue.WaitablePriorityQueueSem;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ThreadPool implements Executor {
    private WaitablePriorityQueueSem<Task<?>> wpq;
    private int numOfThread; //(> 0)

    public ThreadPool(int numberOfThread) {
        numOfThread = numberOfThread;
        wpq = new WaitablePriorityQueueSem<>(numberOfThread);
    }

    public enum Priority {
        LOW,
        MED,
        HIGH
    }

    public Future<Void> submit(Runnable task, Priority priority) {}
    // inside we transfer runnable task to callable

    public <T> Future<T> submit(Runnable task, Priority priority, T returnValue) {}

    public <T> Future<T> submit(Callable<T> task, Priority priority) throws InterruptedException {
        Task creaTask = new Task<>(task,priority);
        wpq.enqueue(creaTask);
        return creaTask.anotherHolder;
        //return null;
    }

    public <T> Future<T> submit(Callable<T> task) {
        return null;
    }

    public void execute(Runnable run) {
        //calls submit with default priority, creates callable ans submits its to the wpq
    }

    public void setNumberOfThreads(int numberOfThreads) {
    } // numberOfTHreads > 0 // problem if numberOfThreads is less than in Ctor, (the number of threads will be decreased)

    public void pause() {
    } // after pause threads wont take tasks from the queue

    public void resume() {
    } // reverse pause operation

    public void shutdown() {
    } // after shutdown submit will throw exceptions, nothing will work. all current tasks in the queue will execute. not blocking

    public void awaitTermination() {
    } // wait for all threads to finish?

    public void awaitTermination(long timeout, TimeUnit unit) {
    }


    private class Task<T> implements Comparable<Task<?>> {
        private Priority priority;
        private TaskFuture anotherHolder;
        private Callable<T> call;
        private T result;
        private AtomicBoolean doneFlag = new AtomicBoolean(false);

        public Task(T task, T priority) {}
        //TaskFutre or Task should hold reference each other somehow||

        void execute() throws Exception {
            result = call.call();
        }

        @Override
        public int compareTo(Task<?> task) {
            return this.priority.compareTo(task.priority);

        }

        private class TaskFuture implements Future<T>{
            private Task<T> holder;
            public boolean cancel(){return true;};

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
                return holder.result;
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
