import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def solve_graph_project():
    # 1. Input: The Adjacency List
    # قمت بتعريفها هنا كقاموس (Dictionary) يمثل الغراف
    # A متصلة بـ B و C، وهكذا...
    adj_list = {
        'A': ['B', 'C'],
        'B': ['A', 'D', 'E'],
        'C': ['A', 'F'],
        'D': ['B'],
        'E': ['B', 'F'],
        'F': ['C', 'E']
    }

    # الحصول على قائمة بجميع الرؤوس (Vertices) مرتبة أبجدياً
    nodes = sorted(adj_list.keys())
    num_nodes = len(nodes)
    
    # عمل خريطة لربط كل حرف برقم (Index) للمصفوفة
    # A->0, B->1, ...
    node_to_index = {node: i for i, node in enumerate(nodes)}

    print("-" * 30)
    print("1. Adjacency List (Input):")
    for node, neighbors in adj_list.items():
        print(f"  {node}: {neighbors}")

    # ---------------------------------------------------------
    # Task 1: Convert to Adjacency Matrix
    # ---------------------------------------------------------
    # إنشاء مصفوفة اصفار بحجم N*N
    adj_matrix = np.zeros((num_nodes, num_nodes), dtype=int)

    for node, neighbors in adj_list.items():
        u = node_to_index[node]
        for neighbor in neighbors:
            v = node_to_index[neighbor]
            adj_matrix[u][v] = 1 # وضع 1 عند وجود اتصال

    print("\n" + "-" * 30)
    print("2. Adjacency Matrix (Output):")
    
    # طباعة أسماء الأعمدة
    print("  ", end=" ")
    for n in nodes:
        print(n, end=" ")
    print()
    
    # طباعة المصفوفة مع أسماء الصفوف
    for i, row in enumerate(adj_matrix):
        print(f"{nodes[i]} {row}")

    # ---------------------------------------------------------
    # Task 2: Draw Graph & Count Paths
    # ---------------------------------------------------------
    # سنستخدم مكتبة NetworkX للرسم وحساب المسارات
    G = nx.Graph(adj_list)

    print("\n" + "-" * 30)
    print("3. Path Counting:")
    
    # مثال: حساب المسارات بين A و F
    start_node = 'A'
    end_node = 'F'
    
    if start_node in G and end_node in G:
        # هذه الدالة تجد كل المسارات البسيطة (بدون تكرار)
        paths = list(nx.all_simple_paths(G, source=start_node, target=end_node))
        print(f"Number of simple paths between {start_node} and {end_node}: {len(paths)}")
        print("The paths are:")
        for p in paths:
            print(" -> ".join(p))
    else:
        print("Start or End node not found.")

    # الرسم
    print("\n[INFO] Drawing the graph... check the popup window.")
    plt.figure(figsize=(8, 6))
    pos = nx.spring_layout(G)  # تحديد طريقة توزيع النقاط
    
    # رسم العقد والأضلاع
    nx.draw(G, pos, 
            with_labels=True, 
            node_color='skyblue', 
            node_size=2000, 
            edge_color='gray', 
            font_size=15, 
            font_weight='bold')
            
    plt.title("Graph Visualization")
    plt.show()

if __name__ == "__main__":
    solve_graph_project()