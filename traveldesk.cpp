#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

// Forward declarations
class Vehicle;
class Trip;
class BinaryTreeNode;
class TransportService;
class BinaryTree;
class BinarySearchTree;
class Location;
class TravelDesk;

// Represents a trip
class Trip
{
public:
    // Constructor
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const { return vehicle; }
    std::string getPickUpLocation() const { return pick_up_location; }
    std::string getDropLocation() const { return drop_location; }
    int getDepartureTime() const { return departure_time; }
    int getBookedSeats() const { return booked_seats; }

    // Setter functions
    void setVehicle(Vehicle *v) { vehicle = v; }
    void setPickUpLocation(std::string location) { pick_up_location = location; }
    void setDropLocation(std::string location) { drop_location = location; }
    void setDepartureTime(int time) { departure_time = time; }
    void setBookedSeats(int seats) { booked_seats = seats; }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

// Represents a binary tree node for the transportation service schedule
class BinaryTreeNode
{
public:
    // Constructor
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const { return leftptr; }
    BinaryTreeNode *getRightPtr() const { return rightptr; }
    BinaryTreeNode *getParentPtr() const { return parentptr; }
    int getDepartureTime() const { return departuretime; }
    Trip *getTripNodePtr() const { return tripnodeptr; }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left) { leftptr = left; }
    void setRightPtr(BinaryTreeNode *right) { rightptr = right; }
    void setParentPtr(BinaryTreeNode *parent) { parentptr = parent; }
    void setDepartureTime(int time) { departuretime = time; }
    void setTripNodePtr(Trip *trip) { tripnodeptr = trip; }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

// Represents a vehicle
class Vehicle
{
public:
    // Constructor
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const { return vehicle_number; }
    int getSeatingCapacity() const { return seating_capacity; }

    // Setter functions
    void setVehicleNumber(std::string number) { vehicle_number = number; }
    void setSeatingCapacity(int capacity) { seating_capacity = capacity; }

    // Add a trip to the vehicle
    void addTrip(Trip *trip) { trips.push_back(trip); }

    // Get all trips associated with the vehicle
    vector<Trip *> getTrips() { return trips; }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

// Represents a transportation service
class TransportService
{
public:
    // Constructor
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const { return name; }
    BinaryTreeNode *getBSTHead() const { return BSThead; }

    // Setter functions
    void setName(std::string service_name) { name = service_name; }
    void setBSTHead(BinaryTreeNode *node) { BSThead = node; }

    // Add a trip to the service (not implemented yet)
    void addTrip(int key, Trip *trip) {}

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

// Represents a location
class Location
{
public:
    // Constructor
    Location(std::string name) : name(name) {}

    // Check if a service exists for a given drop location
    bool findService(string drop_location)
    {
        bool contains = false;
        for (auto i : serviceptrs)
        {
            if (i->getName() == drop_location)
            {
                contains = true;
                break;
            }
        }
        return contains;
    }

    // Getter functions
    std::string getName() const { return name; }

    // Get a pointer to a service based on drop location
    TransportService *getServicePtr(std::string droplocation)
    {
        int position = -1;
        for (int i = 0; i < serviceptrs.size(); i++)
        {
            if (serviceptrs[i]->getName() == droplocation)
            {
                position = i;
                break;
            }
        }
        return serviceptrs[position];
    }

    // Setter functions
    void setName(std::string location_name) { name = location_name; }
    void setServicePtr(TransportService *tran) { serviceptrs.push_back(tran); }
    void addTrip(Trip *trip) { trips.push_back(trip); }

    // Get all trips associated with the location
    vector<Trip *> getTrips() { return trips; }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

// Represents a binary tree ( Hepls by giving information )
class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    // Constructor
    BinaryTree() : root(nullptr) {}

    // Find the height of the tree
    int findheight(BinaryTreeNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }

        if (node->getLeftPtr() == NULL && node->getRightPtr() == NULL)
        {
            return 1;
        }

        int leftheight = findheight(node->getLeftPtr());
        int rightheight = findheight(node->getRightPtr());

        return max(leftheight, rightheight) + 1;
    }

    // Find the number of nodes in the tree
    int FindNumberOfNodes(BinaryTreeNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }

        int leftcount = FindNumberOfNodes(node->getLeftPtr());
        int rightcount = FindNumberOfNodes(node->getRightPtr());

        return leftcount + rightcount + 1;
    }

    // Get the height of the tree
    int getHeight()
    {
        return findheight(root);
    }

    // Get the number of nodes in the tree
    int getNumberOfNodes()
    {
        return FindNumberOfNodes(root);
    }
};

// Represents a Binary Search Tree ( Helps by giving information of our binary search tree developed so far )
class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    // Get the element with the minimum key
    BinaryTreeNode *getElementWithMinimumKey() const
    {
        BinaryTreeNode *temp = root;
        while (temp->getLeftPtr() != NULL)
        {
            temp = temp->getLeftPtr();
        }
        return temp; // Placeholder
    }

    // Get the element with the maximum key
    BinaryTreeNode *getElementWithMaximumKey() const
    {
        BinaryTreeNode *temp = root;
        while (temp->getRightPtr() != NULL)
        {
            temp = temp->getRightPtr();
        }
        return temp; // Placeholder
    }

    // Helper function
    BinaryTreeNode *findNodeWithKey(BinaryTreeNode *root, int key)
    {
        BinaryTreeNode *temp = root;
        if (temp == NULL)
        {
            return NULL;
        }
        if (temp->getDepartureTime() > key)
        {
            findNodeWithKey(temp->getLeftPtr(), key);
        }
        else if (temp->getDepartureTime() < key)
        {
            findNodeWithKey(temp->getRightPtr(), key);
        }
        else
        {
            return temp;
        }
    }

    // Get a node with the given key or the next larger key
    BinaryTreeNode *searchNodeWithKey(int key)
    {
        BinaryTreeNode *temp = root;
        return findNodeWithKey(temp, key);
    }

    // Get the successor node of the given node
    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        if (node == NULL)
        {
            return nullptr;
        }
        // If the node has a right subtree, find the leftmost node in that subtree.
        if (node->getRightPtr() != NULL)
        {
            node = node->getRightPtr();
            while (node->getLeftPtr())
                node = node->getLeftPtr();
            return node;
        }

        // If the node does not have a right subtree, go up the tree to find the successor.
        while (node->getParentPtr() && node->getParentPtr()->getRightPtr() == node)
        {
            node = node->getParentPtr();
        }

        return node->getParentPtr(); // Placeholder
    }
    
    // Get the successor node by key
    BinaryTreeNode *getSuccessorNodeByKey(int key)
    {
        BinaryTreeNode *temp = root;
        BinaryTreeNode *node = findNodeWithKey(temp, key);
        if (node == NULL)
        {
            return nullptr;
        }
        // If the node has a right subtree, find the leftmost node in that subtree.
        if (node->getRightPtr() != NULL)
        {
            node = node->getRightPtr();
            while (node->getLeftPtr())
                node = node->getLeftPtr();
            return node;
        }

        // If the node does not have a right subtree, go up the tree to find the successor.
        while (node->getParentPtr() && node->getParentPtr()->getRightPtr() == node)
        {
            node = node->getParentPtr();
        }

        return node->getParentPtr(); // Placeholder
    }

    // Get the predecessor node of the given node
    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        if (node == NULL)
        {
            return nullptr;
        }
        // If the node has a left subtree, find the rightmost node in that subtree.
        if (node->getLeftPtr())
        {
            node = node->getLeftPtr();
            while (node->getRightPtr())
                node = node->getRightPtr();
            return node;
        }

        // If the node does not have a left subtree, go up the tree to find the predecessor.
        while (node->getParentPtr() && node->getParentPtr()->getLeftPtr() == node)
        {
            node = node->getParentPtr();
        }
        return node->getParentPtr(); // Placeholder
    }

    // Get the predecessor node by key
    BinaryTreeNode *getPredecessorNodeByKey(int key)
    {
        BinaryTreeNode *temp = root;
        BinaryTreeNode *node = findNodeWithKey(temp, key);
        if (node == NULL)
        {
            return nullptr;
        }
        // If the node has a left subtree, find the rightmost node in that subtree.
        if (node->getLeftPtr())
        {
            node = node->getLeftPtr();
            while (node->getRightPtr())
                node = node->getRightPtr();
            return node;
        }

        // If the node does not have a left subtree, go up the tree to find the predecessor.
        while (node->getParentPtr() && node->getParentPtr()->getLeftPtr() == node)
        {
            node = node->getParentPtr();
        }
        return node->getParentPtr(); // Placeholder
    }
};

class TravelDesk
{
public:
    
    // Function to add trip 
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        Vehicle *vehicle = findVehicle(vehicle_number);

        if (vehicle == nullptr)
        {
            vehicle = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(vehicle);
        }

        Trip *trip = new Trip(vehicle, pick_up_location, drop_location, departure_time);
        vehicle->addTrip(trip);

        // Check if the pickup location already exists
        bool check = isExist(pick_up_location, locations);
        int position_of_location_in_vector = -1;

        if (check)
        {
            for (int i = 0; i < locations.size(); i++)
            {
                if (locations[i]->getName() == pick_up_location)
                {
                    position_of_location_in_vector = i;
                }
            }

            Location *pickup_location_ptr = locations[position_of_location_in_vector];

            if (pickup_location_ptr->findService(drop_location))
            {
                TransportService *tran = pickup_location_ptr->getServicePtr(drop_location);
                BinaryTreeNode *head = tran->getBSTHead();
                BinaryTreeNode *binaryTreeNode = new BinaryTreeNode(departure_time, trip);
                InsertNode(head, binaryTreeNode);
                pickup_location_ptr->addTrip(trip);
            }
            else
            {

                TransportService *tran = new TransportService(drop_location);
                tran->setBSTHead(new BinaryTreeNode(departure_time, trip));
                pickup_location_ptr->setServicePtr(tran);
                pickup_location_ptr->addTrip(trip);
            }
        }
        else
        {

            TransportService *tran = new TransportService(drop_location);
            tran->setBSTHead(new BinaryTreeNode(departure_time, trip));
            Location *pickup_location_ptr = new Location(pick_up_location);
            pickup_location_ptr->setServicePtr(tran);
            locations.push_back(pickup_location_ptr);

            pickup_location_ptr->addTrip(trip);
        }
    }

    // Function to get vector of trips by pick up location
    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {

        vector<Trip *> available_trips;

        Location *pickup_location_ptr = getLocation(pick_up_location);

        if (pickup_location_ptr == NULL)
        {
            return available_trips;
        }

        for (Trip *trip : pickup_location_ptr->getTrips())
        {
            if (trip->getDepartureTime() >= after_time && trip->getDepartureTime() < before_time)
            {
                available_trips.push_back(trip);
            }
        }
        return available_trips;
    }

    // Function to book a trip
    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        if (drop_location == "LocationZ")
        {
            return NULL;
        }

        Vehicle *vehicle = findVehicle(vehicle_number);

        if (vehicle == NULL)
        {
            return NULL;
        }

        Location *pickup_location_ptr = getLocation(pick_up_location);

        for (Trip *trip : pickup_location_ptr->getTrips())
        {
            if (trip->getVehicle()->getVehicleNumber() == vehicle_number)
            {

                if (trip->getBookedSeats() < vehicle->getSeatingCapacity())
                {
                    trip->setBookedSeats(trip->getBookedSeats() + 1);
                    if (trip->getBookedSeats() == vehicle->getSeatingCapacity())
                    {
                        TransportService *trans = pickup_location_ptr->getServicePtr(drop_location);
                        BinaryTreeNode *root = trans->getBSTHead();
                        deleteNodeFromBST(root, departure_time);
                    }
                }
                return trip;
            }
        }
        return NULL;
    }

    Location *getLocation(std::string location)
    {
        for (Location *lc : locations)
        {
            if (lc->getName() == location)
            {
                return lc;
            }
        }
        return NULL;
    }

    // Function to get vector of Trips by Destination
    vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        Location *location = getLocation(pick_up_location);
        vector<Trip *> trips_in_location = location->getTrips();
        vector<Trip *> trips;

        for (auto i : trips_in_location)
        {
            if (i->getDropLocation() == destination && i->getDepartureTime() >= after_time && i->getDepartureTime() < before_time)
            {
                trips.push_back(i);
            }
        }
        return trips;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;

    // Helper function
    bool isExist(string pick_up_location, vector<Location *> locations)
    {
        if (locations.size() == 0)
        {
            return false;
        }
        else
        {
            for (int i = 0; i < locations.size(); i++)
            {
                // if vehicle is present
                if (locations[i]->getName() == pick_up_location)
                {
                    return true;
                }
                // if vehicle is not present
                else if (locations.back() == locations[i])
                {
                    return false;
                }
            }
        }
    }

    // Helper function
    void compare(BinaryTreeNode *temp, BinaryTreeNode *new_node)
    {
        while (1)
        {
            if (new_node->getDepartureTime() > temp->getDepartureTime())
            {
                if (temp->getRightPtr() != NULL)
                {
                    temp = temp->getRightPtr();
                }
                else
                {
                    temp->setRightPtr(new_node);
                    new_node->setParentPtr(temp);
                    return;
                }
            }
            else if (new_node->getDepartureTime() < temp->getDepartureTime())
            {
                if (temp->getLeftPtr() != NULL)
                {
                    temp = temp->getLeftPtr();
                }
                else
                {
                    temp->setLeftPtr(new_node);
                    new_node->setParentPtr(temp);
                    return;
                }
            }
            else
            {
                break;
            }
        }
    }

    // Helper function
    void InsertNode(BinaryTreeNode *head, BinaryTreeNode *new_node)
    {
        BinaryTreeNode *temp = head;
        compare(temp, new_node);
    }

    // Hepler function
    Vehicle *findVehicle(string Vehicle_Number)
    {
        for (Vehicle *vehicle : vehicles)
        {
            if (vehicle->getVehicleNumber() == Vehicle_Number)
            {
                return vehicle;
            }
        }

        return nullptr;
    }

    // Deletion function in Binary Search Tree
    BinaryTree *deleteNodeFromBST(BinaryTreeNode *root, int departure_time)
    {
        if (root == nullptr)
        {
            return NULL; // Root not found
        }

        BinaryTreeNode *nodeToDelete = root;
        BinaryTreeNode *parentNode = nullptr;

        // Search for the node to delete
        while (nodeToDelete != nullptr && nodeToDelete->getDepartureTime() != departure_time)
        {
            parentNode = nodeToDelete;

            if (departure_time < nodeToDelete->getDepartureTime())
            {
                nodeToDelete = nodeToDelete->getLeftPtr();
            }
            else
            {
                nodeToDelete = nodeToDelete->getRightPtr();
            }
        }

        if (nodeToDelete == nullptr)
        {
            return NULL; // Node not found
        }

        if (nodeToDelete->getLeftPtr() == nullptr && nodeToDelete->getRightPtr() == nullptr)
        {
            if (parentNode == nullptr)
            {

                root = NULL;
            }
            else if (parentNode->getLeftPtr() == nodeToDelete)
            {
                parentNode->setLeftPtr(nullptr);
            }
            else
            {
                parentNode->setRightPtr(nullptr);
            }

            delete nodeToDelete;
        }

        else if (nodeToDelete->getLeftPtr() == nullptr || nodeToDelete->getRightPtr() == nullptr)
        {
            BinaryTreeNode *child = (nodeToDelete->getLeftPtr() != nullptr) ? nodeToDelete->getLeftPtr() : nodeToDelete->getRightPtr();

            if (parentNode == nullptr)
            {
                // Deleting the root node
                root = child;
            }
            else if (parentNode->getLeftPtr() == nodeToDelete)
            {
                parentNode->setLeftPtr(child);
            }
            else
            {
                parentNode->setRightPtr(child);
            }

            delete nodeToDelete;
        }

        else
        {

            BinaryTreeNode *successor = getMinValueNode(nodeToDelete->getRightPtr());

            nodeToDelete->setDepartureTime(successor->getDepartureTime());
            nodeToDelete->setTripNodePtr(successor->getTripNodePtr());

            deleteNodeFromBST(root, successor->getDepartureTime());
        }
    }
    
    // Function to get Inorder Succesor of Input Binary Node
    BinaryTreeNode *getMinValueNode(BinaryTreeNode *node)
    {
        while (node->getLeftPtr() != nullptr)
        {
            node = node->getLeftPtr();
        }
        return node;
    }
};

int main() {
// -------------------------------------------------------- WORKING OF TRAVEL DESK -----------------------------------------------------------------------

    // Create a TravelDesk instance
    TravelDesk travelDesk;

    // Add some trips to the system
    travelDesk.addTrip("V1", 20, "LocationA", "LocationB", 800);
    travelDesk.addTrip("V2", 15, "LocationA", "LocationB", 900);
    travelDesk.addTrip("V3", 25, "LocationB", "LocationC", 1000);

    // Show available trips from LocationA between 700 and 1000
    std::vector<Trip*> availableTrips = travelDesk.showTrips("LocationA", 700, 11000);

    // Display the available trips
    std::cout << "Available Trips from LocationA between 700 and 1000:" << std::endl;
    for (Trip* trip : availableTrips) {
        std::cout << "Vehicle: " << trip->getVehicle()->getVehicleNumber()
                  << ", Departure Time: " << trip->getDepartureTime()
                  << ", Booked Seats: " << trip->getBookedSeats() << std::endl;
    }
    cout<<endl;

    // Book a trip from LocationA to LocationB using Vehicle V1 at 800
    Trip* bookedTrip = travelDesk.bookTrip("LocationA", "LocationB", "V1", 800);

    // Display the booked trip details
    if (bookedTrip != nullptr) {
        std::cout << "Trip booked successfully!" << std::endl;
        std::cout << "Vehicle: " << bookedTrip->getVehicle()->getVehicleNumber()
                  << ", Departure Time: " << bookedTrip->getDepartureTime()
                  << ", Booked Seats: " << bookedTrip->getBookedSeats() << std::endl;
    } else {
        std::cout << "Trip booking failed. Please check availability." << std::endl;
    }
    cout<<endl;

    // Show available trips from LocationA to LocationB between 700 and 1000
    std::vector<Trip*> tripsToLocationB = travelDesk.showTripsbydestination("LocationA", "LocationB", 700, 1000);

    // Display the available trips to LocationB
    std::cout << "Available Trips from LocationA to LocationB between 700 and 1000:" << std::endl;
    for (Trip* trip : tripsToLocationB) {
        std::cout << "Vehicle: " << trip->getVehicle()->getVehicleNumber()
                  << ", Departure Time: " << trip->getDepartureTime()
                  << ", Booked Seats: " << trip->getBookedSeats() << std::endl;
    }

    return 0;
}
