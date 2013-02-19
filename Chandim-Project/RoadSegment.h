/**
*  @file RoadSegment.h
*   Define a segment of the Road
*/


class RoadSegment
{
  private:
    

    int capacity;         /**< Maximum capacity of the Road */
    int population;       /**< current count */
    Intersection* parent; /**< Parent intersection */
    dir Direction;
    
  public:
              
    VehicleQueue qright;  /**< Right lane (Vehicle queue) */
    VehicleQueue qleft;   /**< Left lane (Vehicle Queue) */
    
    /**
    *  Constructor
    *
    */

    RoadSegment(dir direction, Intersection* par, int cap)
    {
      Direction = direction;
      parent = par;
      capacity = cap;
    }

    /**
    *  Adds vehicle to the road segment
    *
    */
    
    void AddVehicle(VehicleClass* vehicle);

    /**
    *  Evicts vehicle from the Road Segment
    *
    */
    void EvictVehicle();
		    
};
