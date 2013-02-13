
class RoadSegment
{
  private:
    
    int capacity; //max capacity
    int population; //current count
    Intersection* parent;
    dir Direction;
    
  public:
              
    VehicleQueue qright;
    VehicleQueue qleft;
    
    RoadSegment(dir direction, Intersection* par, int cap)
    {
      Direction = direction;
      parent = par;
      capacity = cap;
    }
    
    void AddVehicle(VehicleClass* vehicle);
    void EvictVehicle();
		    
};
