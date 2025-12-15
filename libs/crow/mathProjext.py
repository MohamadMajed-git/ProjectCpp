import networkx as nx
import matplotlib.pyplot as plt
adj_list={
    "A":["B","C","D"],
    "B":["A","E"],
    "C":["A","F"],
    "D":["A","F"],
    "E":["B","F"],
    "F":["C","D","E"],
    "T":["G"],
    "G":["T"]
}
def numberOfpathes(graph,start,end,visited=[]):
    if start==end:
        return 1
    count=0
    visited = visited + [start]
    for neighbor in graph[start]:
        if neighbor not in visited:
            count+=numberOfpathes(graph,neighbor,end,visited)
    return count

print("Adjacency List (input): ")
for key,value in adj_list.items():
    print(f"{key}:{value}")

adj_matrix={}
for key in adj_list.keys():
    adj_matrix[key]={}
    for k in adj_list.keys():
        adj_matrix[key][k]=0

for key,value in adj_list.items():
    for v in value:
        adj_matrix[key][v]=1


print("\n\n\n")
print(adj_matrix)
print("\n\n\n")


print("\nAdjacency Matrix (output): ")
print(" ",end=" ")
for key in adj_list.keys():
    print(f"{key}",end="  ")
print("")

for key,value in adj_matrix.items():
    print(f"{key}",end=" ")
    for k in value.keys():
        print(f"{value[k]}",end="  ")
    print("")



Graph=nx.Graph(adj_list)
print(f"\nNumber of pathes from A to T: {numberOfpathes(adj_list,'A','T')}")
print(f"Number of pathes from A to E: {numberOfpathes(adj_list,'A','E')}")
print(f"Number of pathes from A to A: {numberOfpathes(adj_list,'A','A')}")
print(f"Number of pathes from A to F: {numberOfpathes(adj_list,'A','F')}")
print(f"Number of pathes from C to D: {numberOfpathes(adj_list,'C','D')}")
print(f"Number of pathes from G to T: {numberOfpathes(adj_list,'G','T')}")
nx.draw_spring(Graph,with_labels=True)
plt.show()
