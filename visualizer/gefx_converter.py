import networkx as nx
import sys

def convert_to_gephi(graph_path, solution_path):
    G = nx.Graph()
    
    with open(graph_path, 'r') as f:
        for line in f:
            parts = line.split()
            if not parts or parts[0] in ['c', 'p']: continue
            G.add_edge(parts[0], parts[1])

    solution_nodes = set()
    with open(solution_path, 'r') as f:
        lines = f.readlines()
        if len(lines) > 1:
            solution_nodes = set(l.strip() for l in lines[1:])

    for node in G.nodes():
        G.nodes[node]['is_solution'] = (node in solution_nodes)
        G.nodes[node]['viz'] = {'color': {'r': 255, 'g': 0, 'b': 0} if node in solution_nodes else {'r': 173, 'g': 216, 'b': 230}}

    nx.write_gexf(G, "graph.gexf")
    print("gefx file 'graph.gexf' generated. Open it with Gephi to visualize.")

if __name__ == "__main__":
    convert_to_gephi(sys.argv[1], sys.argv[2])