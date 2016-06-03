import java.util.*;
import java.util.Queue;

class UndirectedGraphNode {
    int label;
    int color;
    ArrayList<UndirectedGraphNode> neighbors;
    UndirectedGraphNode(int x) {
        this.label = x;
        this.color = 0;
        this.neighbors = new ArrayList<UndirectedGraphNode>();
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        for (int i = 1; i <= T; i++) {
            int N = in.nextInt();
            int M = in.nextInt();
            // initialize graph
            List<UndirectedGraphNode> graph = new ArrayList<UndirectedGraphNode>();
            for (int n = 1; n <= N; n++) {
                graph.add(new UndirectedGraphNode(n));
            }
            // construct graph
            for (int j = 1; j <= M; j++) {
                int u = in.nextInt(), v = in.nextInt();
                graph.get(u - 1).neighbors.add(graph.get(v - 1));
                graph.get(v - 1).neighbors.add(graph.get(u - 1));
            }
            // solve
            if (solve(graph)) {
                System.out.println("Correct");
            } else {
                System.out.println("Wrong");
            }
        }
    }

    public static boolean solve(List<UndirectedGraphNode> graph) {
        // 1 for white, -1 for black, 0 for uncolored
        for (UndirectedGraphNode node : graph) {
            if (node.color == 0) {
                node.color = 1;
                Queue<UndirectedGraphNode> q = new LinkedList<UndirectedGraphNode>();
                q.offer(node);
                while (!q.isEmpty()) {
                    int qSize = q.size();
                    for (int i = 0; i < qSize; i++) {
                        UndirectedGraphNode qNode = q.poll();
                        for (UndirectedGraphNode neighbor : qNode.neighbors) {
                            if (neighbor.color == 0) {
                                neighbor.color = -1 * qNode.color;
                                q.offer(neighbor);
                            } else if (neighbor.color + qNode.color != 0) {
                                // the color of qNode is the same with neighbor
                                return false;
                            }
                        }
                    }
                }
            }
        }

        return true;
    }
}
