def sge_algorithm():
    import networkx as nx
    import matplotlib.pyplot as plt
    def connected_graph(G,n):
        pos = nx.get_node_attributes(G,'pos')
        for i in range(1,n+1):
            for j in range(1,n+1):
                if(i!=j):
                    G.add_edge(i,j,weight=((pos[i][0]-pos[j][0])**2 + (pos[i][1]-pos[j][1])**2)**(0.5))
        return G
    def make_graph(x,n):
        if(x==1):
            print("The following data is for the houses with Solar Panels")
        else:
            print("The following data is for the houses which need more electricity")
        G = nx.Graph()
        for i in range(1,n+1):
            print("Enter the (x,y) coordinates for house ",i)
            x = int(input("x coordinate: "))
            y = int(input("y coordinate: "))
            G.add_node(i,pos=(x,y))
        return G
    def set_graph():
        n1 = int(input("Enter the number of houses with excess electricity: "))
        n2 = int(input("Enter the number of houses with needing electricity: "))
        G1 = make_graph(1,n1)
        G2 = make_graph(2,n2)
        G1 = connected_graph(G1,n1)
        G2 = connected_graph(G2,n2)
        c1 = []
        c2 = []
        for node in G1:
            c1.append('green')
        for node in G2:
            c2.append('red')
        return G1, G2, c1, c2, n1, n2
    def setting_energygrid(G1,G2,n1,n2,c1,c2):
        minimum = 9999999999
        gr_1 = 0
        gr_2 = 0
        pos1 = nx.get_node_attributes(G1,'pos')
        pos2 = nx.get_node_attributes(G2,'pos')
        for i in range(1,n1+1):
            for j in range(1,n2+1):
                if(minimum>((pos1[i][0]-pos2[j][0])**2 + (pos1[i][1]-pos2[j][1])**2)**(0.5)):
                    minimum = ((pos1[i][0]-pos2[j][0])**2 + (pos1[i][1]-pos2[j][1])**2)**(0.5)
                    gr_1 = i
                    gr_2 = j
        G1.add_node(n1+1,pos=((pos1[gr_1][0]+pos2[gr_2][0])/2,(pos1[gr_1][1]+pos2[gr_2][1])/2))
        G2.add_node(n2+1,pos=((pos1[gr_1][0]+pos2[gr_2][0])/2,(pos1[gr_1][1]+pos2[gr_2][1])/2))
        G1.add_edge(n1+1,gr_1,weight=((
            (pos1[gr_1][0] - (pos1[gr_1][0]+pos2[gr_2][0])/2)**2 +
            (pos1[gr_1][1] - (pos1[gr_1][1]+pos2[gr_2][1])/2)**2)**(0.5)))       
        G2.add_edge(n2+1,gr_2,weight=((
            (pos2[gr_1][0] - (pos1[gr_1][0]+pos2[gr_2][0])/2)**2 +
            (pos2[gr_1][1] - (pos1[gr_1][1]+pos2[gr_2][1])/2)**2)**(0.5)))
        c1.append('yellow')
        c2.append('yellow')
        return G1, G2, c1, c2
    G1, G2, c1, c2, n1, n2 = set_graph()
    G1_new, G2_new, c1_new, c2_new = setting_energygrid(G1,G2,n1,n2,c1,c2)
    pos1_new = nx.get_node_attributes(G1_new,'pos')
    pos2_new = nx.get_node_attributes(G2_new,'pos')
    giving = nx.minimum_spanning_tree(G1_new)
    taking = nx.minimum_spanning_tree(G2_new)
    fig, ax = plt.subplots(figsize=(10, 10))
    plt.title("Optimized Connections for Excess Electricity transfer (Green is Giving) (Red is Taking) (Yellow is Grid)")
    nx.draw(giving,pos1_new,node_size=20,node_color=c1_new,ax=ax)
    nx.draw(taking,pos2_new,node_size=20,node_color=c2_new,ax=ax)
    ax.set_axis_on()
    ax.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)
    plt.show()
    return
sge_algorithm()