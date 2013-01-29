

class IntersectionwithoutSignal
{
  private:
          int ID;
          bool busy; // busy or not
          VehicleQueue* EBI;
          VehicleQueue* EBO;
          VehicleQueue* WBI;
          VehicleQueue* WBO;
          VehicleQueue* NBI;
          VehicleQueue* NBO;
          VehicleQueue* SBO;
          VehicleQueue* SBI;
         //int curphase; //current phase //needs review
         dir routingtable[12]; //for routing cars
  public:
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         void addVehicletoQueue(VehicleQueue* joinqueue); //Adds to outgoing queue or removes vehicles 
         //constructor:
        IntersectionwithoutSignal( bool stat,dir *table,
		VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
		VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo);
		
        IntersectionwithoutSignal();
         //destructor:
        ~IntersectionwithoutSignal();
  	
};

