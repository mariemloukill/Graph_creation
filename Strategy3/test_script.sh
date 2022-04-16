#!/bin/bash

# Getting the datasets folder
path="/datadrive/dataset"
# Deleting the older results

# putting the filenames into an array 
arr=()
while IFS= read -r line; do
   arr+=("$line")
done < /datadrive/dataset/data_files.txt
echo ${arr[@]}

# looping through the list of files
for i in "${arr[@]}"
do
   : 
   
   echo $i
   file_name=$path/$i  # getting the full file path 
   
   ############################################################
   # starting counter for time getting the number of edges time 
   start=$(date +%s.%N)
   # get the number of edges aka the number of lines in the file
   edges=$(wc -l $file_name| awk '{print $1}')
   #nodes=$( awk '{print $1 "\n" $2}' $file_name |sort|uniq|wc -l | awk '{print $1}')
   end=$(date +%s.%N)
   runtime=$( echo " $end - $start" | bc )
   echo " time to get edges is $runtime seconds and the number of edges is $edges"
   # end of getting the number of edges
   ###########################################################
   a=1
   ############################################################
    #start running each file 10 times
    echo $a
       for VARIABLE in {1..10};
   do
	./main $edges $file_name
	#calling the cpp program
   done
   
   # Getting the average time
  time=$(awk '{ total += $1; count++ } END { print total/10 }' creation_time_edge.txt)
   # Getting the average memory
   memory=$(awk '{ total += $1; count++ } END { print total/10 }' creation_ram_edge.txt)
   
   #filling the results file 
   echo "$i,$edges,$time,$memory">>average_results_edge.csv
   > creation_time_edge.txt #empty file
   > creation_ram_edge.txt  #empty file
   
   #logging the results in historical file
   cat average_results_edge.csv >> average_results_all_edge.txt
   echo "end of $file_name"
   ###########################################################
done
