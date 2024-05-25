package biz.bna.project;

import java.util.*;
import java.util.concurrent.*;

public class Main {

    public static final int THREADS = 50;
    public static final int ITERATIONS = 1000000;
    public static final double NSEC = 1000_000_000.0;
    public static final int MAP_SIZE = 100;
    public static final int SAMPLES = 5;

    public static Map<String, Integer> hashMap = new HashMap<>();
    public static Map<String, Integer> hashTable = new Hashtable<>();
    public static Map<String, Integer> syncMap = Collections.synchronizedMap(new HashMap<>());
    public static Map<String, Integer> cHashMap = new ConcurrentHashMap<>();

    public static void main(String[] args) {

        System.out.println("Collections:");
        double hashMapTime = compute(hashMap) / NSEC;
        double hashTableTime = compute(hashTable) / NSEC;
        double syncMapTime = compute(syncMap) / NSEC;
        double cHashMapTime = compute(cHashMap) / NSEC;

        System.out.println("Execution times:");
        System.out.println(String.format("\tHashMap: %.3f s,\n\tHashTable: %.3f s,\n\tSyncMap: %.3f s,\n\tConcurrentHashMap: %.3f s.",
                hashMapTime, hashTableTime, syncMapTime, cHashMapTime));
    }

    private static long compute(Map<String, Integer> map) {

        System.out.print(String.format("\t%s", map.getClass().getName()));

        long start = 0;
        long stop = 0;

        for (int k = 0; k < SAMPLES; k++) {

            start = System.nanoTime();

            ExecutorService executorService = Executors.newFixedThreadPool(THREADS);

            List<Callable<String>> tasks = new ArrayList<>();
            List<Future<String>> results = new ArrayList<>();

            // create a list of tasks
            for (int i = 0; i < THREADS; i++) {
                tasks.add(() -> {
                    String threadName = Thread.currentThread().getName();
                    Integer num = (int) Math.ceil(Math.random() * MAP_SIZE);
                    for (int j = 0; j < ITERATIONS; j++) {
                        Integer value = map.get(String.valueOf(num));
                        map.put(String.valueOf(num), num);
                    }
                    return "Thread " + threadName + " done";
                });
            }

            // invoke all the tasks
            try {
                results = executorService.invokeAll(tasks);
            } catch (InterruptedException ie) {
                ie.printStackTrace();
            }

            // get results from futures
            try {
                for (Future<String> result : results) {
                    String s = result.get();
                    // System.out.println(s);
                }
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }

            // shutdown executor service
            executorService.shutdown();

            stop = System.nanoTime();
        }

        System.out.println("...done.");

        return stop - start;
    }
}

