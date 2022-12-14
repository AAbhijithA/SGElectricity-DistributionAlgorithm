# SGElectricity-DistributionAlgorithm
(Uses matplotlib and networkx) & (also done in C but only the end result in adjaceny matrix (no visulaization))
### Note!
Please refer to the src files for details and on the process and understanding of the algorithm code
# About the Algorithm
This following project uses The Minimum Spanning Tree over the connected components
(Here the two connected components are the Giving houses and the taking houses)
This aims to help direct the flow of the excess electricity to a grid and then redistribute
it to houses which need electricity

(refer to ipynb for better interactivity else use py file in src)

This is a very useful approach in todays day and scenario
as this approach can efficiently help us to direct the electricity and 
also check the electric consumption by each person who needs it and track
who gives the electricity by the grid but we also have to optimize the number of it
as we can lose energy in transmission and storage if we have too many grids and also 
so someone can not overuse the solar electricity generated by someone else 
by directly connecting it to them

The Minimum Spanning Tree algorithm has been used for finding the most minimized costs
We will focus on our application here

# How the Idea works
(Note: The weights here are the distance between each vertex as a 2D plane)

lets assume green is the houses giving the electricity (excess) and red is the ones taking it (needy)
and 5 of each as shown
and we also assume that the two categories of houses are going to be connected componenents

![](Result/Image1.png)

Now we place a grid by finding the least distance between the vertex pair of the needy and giving components 
(assuming fairness in recieve and transmission)and place it in between so the yellow vertex is going to be the
energy grid

![](Result/Image2.png)

Now we use a Minimum Spanning Tree Algorithm to find the Minimum Spanning Tree for both connected components
(Kruskals or Prims)

![](Result/Image3.png)


