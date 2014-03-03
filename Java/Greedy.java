// Andrei Parvu

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Greedy {

  private final static int NMAX = 500005;

  private static class Pair implements Comparable<Pair> {
    public int master, slave;

    public Pair() {
      this.master = this.slave = 0;
    }

    public Pair(int a, int b) {
      this.master = a;
      this.slave = b;
    }

    public int compareTo(Pair other) {
      if (this.master == other.master) {
        return this.slave - other.slave;
      }
      return this.master - other.master;
    }
  }

  public static void main(String[] args) {
    int n = 0;
    Pair[] cost = new Pair[NMAX];

    try {
      Scanner s = new Scanner(new File("date.in"));
      n = s.nextInt();

      for (int i = 1; i <= n; i++) {
        cost[i] = new Pair();

        cost[i].master = s.nextInt();
        cost[i].slave = s.nextInt();
      }
    } catch (IOException ex) {}

    int rez = cost[1].slave + cost[n].master;

    PriorityQueue<Pair> heap = new PriorityQueue<Pair>();

    boolean[] slaves = new boolean[2 * n + 1];
    slaves[1] = true;
    for (int i = 2; i < n; i += 2) {
      rez += cost[i].master + cost[i + 1].master;

      heap.add(new Pair(cost[i].slave - cost[i].master, i));
      heap.add(new Pair(cost[i + 1].slave - cost[i + 1].master, i + 1));

      Pair p = heap.poll();
      rez += p.master;

      slaves[p.slave] = true;
      System.out.println(p.slave);
    }

    try {
      PrintWriter pw = new PrintWriter("date.out");
      pw.println(rez);

      int p1 = 1, p2 = 1;

      for (int i = 0; i < n; i += 2, p1++, p2++) {
        for (; slaves[p1] == true; p1++);
        for (; slaves[p2] == false; p2++);

        pw.println(p1 + " " + p2);
        System.out.println(p1 + " " + p2);
      }
      pw.flush();
    } catch (FileNotFoundException ex) {}
  }
}
