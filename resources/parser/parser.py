import sys
if (len(sys.argv)>1):
 	f1 = open(sys.argv[1])
 	print "file name is:" , sys.argv[1]
else:
	print "Default file used"
	f1 = open("trajectories-0400pm-0415pm_editted.csv");
	# sys.exit()

if (len(sys.argv)>2):
 	f2 = open(sys.argv[2]);
 	print "Output file name is:" , sys.argv[2]
else:
	print "Default output file used"
	f2 = open("out.csv","w");
	# sys.exit()

if (len(sys.argv)>3):
 	f3 = open(sys.argv[3]);
 	print "Second Output file name is:" , sys.argv[3]
else:
	print "Default second output file used"
	f3 = open("out2.csv","w");
	# sys.exit()

# reading the input file
s = f1.readlines();



orig_count       = [0] * 124
orig_LastAbsTime = [0] * 124
orig_time        = [0] * 124

#finding max vehicle ID
max_ID=0
for i in range( 1 , len(s) ): # Starting from the second line
	currID=int(s[i].split(',')[0]);
	max_ID=max(max_ID,currID)

#initializing variables
lastID=0;	#last vehicle read, to avoid multiple data for one vehicle
currID=0;	#current vehicle's ID
Veh_Len  	=[0.0] * (max_ID+1)
Veh_Class 	=[0] * (max_ID+1)
Org_Zone	=[0] * (max_ID+1)
Dest_Zone	=[0] * (max_ID+1)
Veh_maxTime	=[0.0] * (max_ID+1)
Veh_minTime	=[100000000000.0] * (max_ID+1)

for i in range( 1 , len(s) ): # Starting from the second line
	currID=int(s[i].split(',')[0]);  	
	Veh_minTime[currID]=min(Veh_minTime[currID],float(s[i].split(',')[3 ]))
	Veh_maxTime[currID]=max(Veh_minTime[currID],float(s[i].split(',')[3 ]))
	if lastID != currID :
		Veh_Len  [currID]= float(s[i].split(',')[8 ])
		Veh_Class[currID]= int  (s[i].split(',')[10])
		Org_Zone [currID]= int  (s[i].split(',')[14])
		Dest_Zone[currID]= int  (s[i].split(',')[15])
		lastID=currID;

f2.write("Vehicle_ID,Veh_Len,Veh_Class,Org_Zone,Dest_Zone,Veh_minTime,Veh_maxTime\n");
for i in range(1,max_ID+1) :
		if(Veh_Len[i] != 0) :
			f2.write('%d,%f,%d,%d,%d,%f,%f\n' 
				% (i,Veh_Len[i],Veh_Class[i],Org_Zone[i],Dest_Zone[i],
				Veh_minTime[i],Veh_maxTime[i]))
			# orig=Org_Zone[i]
			# if orig_count[orig]>0 :
			# 	orig_time[orig] = (orig_time[orig] *(orig_count[orig]-1)+
			# 		(Epoch_ms[veh]-orig_LastAbsTime[orig])/1000)/(orig_count[orig])
			# if orig==101:
			# 	print orig, orig_count[orig], orig_time[orig],Epoch_ms[veh],orig_LastAbsTime[orig]
			# orig_count[orig]+=1
			# orig_LastAbsTime[orig]=Epoch_ms[veh]


# f3.write("Org_Zone,count,mean time\n");
# for i in range(101,124) :
# 	f3.write('%d,%d,%f\n' %(i, orig_count[i], orig_time[i]));



f1.close();
f2.close();
f3.close();


print "Total Data lines	=	" , len(s);
print "Total vehicles  	=	" , (max_ID);
print "last vehicle:";
print "ID         		=	" , max_ID;
print "len        		=	" , Veh_Len   [max_ID];
print "Dest_Zone  		=	" , Dest_Zone [max_ID];


# Vehicle_ID,		Frame_ID,		Tot_Frames,		Epoch_ms,		
# Local_X,			Local_Y,		Global_X,		
# Global_Y,			Veh_Len,		Veh_Wid,		Veh_Class,
# Veh_Velocity,		Vehicle_Acc,	Lane_ID,	
# Org_Zone,			Dest_Zone,		Intersection,	Section,
# Direction,		Movement,		Preceding_Veh,	
# Following_Veh,	Spacing,		Headway

# 1- Vehicle_ID
# 4- Epoch_ms
# 9- Veh_Len
# 11- Veh_Class
# 15- Org_Zone
# 16- Dest_Zone
