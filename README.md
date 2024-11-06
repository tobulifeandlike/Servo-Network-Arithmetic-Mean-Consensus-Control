# Servo-Network-Arithmetic-Mean-Consensus-Control
This is a demo of arithmetic mean consensus control strategy application to actual physical system. It contains three servo motors controlled by three arduino boards. To realize the communication among the boards, the I2C protocol is used.

Average Consensus Control Basics  
  To formulate a consensus control problem, a multi-agent system with a state variation function 
x'=f(x(t),u(t)) is used to provide the system dynamics. x(t) is the agent state and u(t) denotes input of the system. Both x and u are vectors. The goal of consensus control is to find a proper control input u so that the system can converge to an agreement value, in the average consensus case, this agreement value is the average of sum of initial conditions of agents in the system. 
To organize the work of the systems, a network is used to connect the agents and realize information exchange. The key term to generalize the information flow is graph Laplacian L which is derived by D-A, D is degree matrix denoting how many connections each agent owns and A is adjacency matrix denoting whether or not there exists a connection between two nodes in the network. 

  To realize the average consensus control, the simplest way for generalizing system dynamic is an integral formula: x' = -Lx. L is the graph Laplacian denoting the network dynamics. In the continuous case, systems in the network will always converge to a common value since all eigenvalues of graph Laplacian are non-negative.    

  To apply the method in some computer simulation cases or physical systems, it might be necessary to discretize the process. The discrete form of the state space model x' = -Lx will become x[k+1] = Px[k]. P is called Perron matrix which is equal to I-eL, I is identity matrix, e is a rate decided by the maximum degree of node in the system network graph topology, L is graph Laplacian.  

Demo Application  
  I2C-a communication protocol that defines a master device and several slave devices to realize the information exchange. For data transmission, master device sends commands to request data from slaves or sends data to slaves thus realizing the information exchange. Using I2C, one will organize a centralized control network. All data transmissions are initiated by master device.
  Control procedure of the servo network-for master, it firstly collect angle information from slaves, then send its angle information to slaves. Finally adjust the servo's angle based on angles collected from slaves. For slaves, they firstly send the angle values to the master to respond the request, then receive the master's angle information. Finally adjust angle of servo motors controlled by them.   
