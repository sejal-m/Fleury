import matplotlib.pyplot as plt
import networkx as nx
from itertools import combinations
import random



def ER(n, p):
    V = set([v for v in range(n)])
    E = set()
    for combination in combinations(V, 2):
        a = random.random()
        if a < p:
            E.add(combination)

    g = nx.Graph()
    g.add_nodes_from(V)
    g.add_edges_from(E)

    return g

print('hello world')

n = 100
p = 0.4
G = ER(n, p)
python_file = open("welsh_powell_input.txt", "w")
for node1, node2 in G.edges():
    data = str(node1) + ' '+ str(node2) + '\n'
    python_file.write(data)

python_file.close()

pos = nx.spring_layout(G)
nx.draw_networkx(G, pos)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
plt.title("Random Graph Generation Example")
plt.show()

