import networkx as nx
import matplotlib.pyplot as plt
import sys
	
def visualize_dimacs_with_solution(graph_path, solution_path):
	G = nx.Graph()
	
	with open(graph_path, 'r') as f:
		for line in f:
			parts = line.split()
			if not parts or parts[0] == 'c':
				continue
			if parts[0] == 'p':
				print(f"Graph: {parts[2]} vertices, {parts[3]} edges")
				for i in range(1, int(parts[2]) + 1):
					G.add_node(str(i))
			else:
				G.add_edge(parts[0], parts[1])

	solution_nodes = set()
	if solution_path:
		try:
			with open(solution_path, 'r') as f:
				lines = f.readlines()
				if lines:
					count = lines[0].strip()
					print(f"Solution: {count} vertices expected")
					for line in lines[1:]:
						node = line.strip()
						if node:
							solution_nodes.add(node)
		except FileNotFoundError:
			print(f"Erreur : Le fichier solution #{solution_path} est introuvable.")

	color_map = []
	for node in G.nodes():
		if node in solution_nodes:
			color_map.append('red')
		else:
			color_map.append('lightblue')

	plt.figure(figsize=(10, 8))
	pos = nx.spring_layout(G, k=0.1, iterations=1)
	
	nx.draw(G, pos, 
			with_labels=True, 
			node_color=color_map, 
			edge_color='lightgray',
			node_size=500,
			font_size=10)
	
	plt.title(f"Graphe: {graph_path} | Solution en Rouge")
	plt.show()

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print(f"Usage: python #{sys.argv} <graph_file> [solution_file]")
	else:
		visualize_dimacs_with_solution(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None)