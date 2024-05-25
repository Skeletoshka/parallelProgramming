package biz.bna.project;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class Main {
    private static int THREADS = 4;
    private static int EXECUTORS = 2;
    private static final Semaphore semaphore = new Semaphore(EXECUTORS);
    private static final MySemaphore mySemaphore = new MySemaphore(EXECUTORS);

    public static void main(String[] args){
        runTask(semaphore);
        runTask(mySemaphore);
    }

    public static void runTask(Semaphore semaphore){
        ExecutorService es = Executors.newFixedThreadPool(THREADS);
        List<Callable<String>> tasks = new ArrayList<>();
        List<Future<String>> results = new ArrayList<>();
        for(int i = 0; i < THREADS; i++){
            tasks.add(() -> {
                String threadName = Thread.currentThread().getName();
                System.out.printf("Thread %s wait\n", threadName);
                semaphore.acquire();
                System.out.printf("Thread %s start\n", threadName);
                for(int j = 0; j < 1000000; j++){
                    Math.sqrt(j);
                }
                System.out.printf("Thread %s release\n", threadName);
                semaphore.release();
                return "Thread" + "done";
            });
        }
        try {
            results = es.invokeAll(tasks);
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        es.shutdown();
    }
}
