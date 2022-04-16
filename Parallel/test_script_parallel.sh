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


   ############################################################
   nb_splits=(5 10 12 20 30 40 50 60 70 80 90 100)
   for nb in "${nb_splits[@]}"
   do
       :
       ############################################################
       # starting counter for time splitting the file
       start=$(date +%s.%N)
       mkdir splitfiles # folder for the new split files
       split_lines=$((($edges / $nb) +1))
       echo "split lines is $split_lines"
       split --lines=$split_lines $file_name splitfiles/$i
       end=$(date +%s.%N)
       splittime=$( echo " $end - $start" | bc )
       echo " time splitting files is  $splittime seconds"
       # end of splitting file
       ###########################################################
       ############################################################
       # start running each file 10 times
       for VARIABLE in {1..10};
       do
	  ./main  #calling the cpp program
       done
       rm -r splitfiles  #delete the folder of split files after each file is done 10 times

       # Getting the average time
  	creation_time=$(awk '{ total += $1; count++ } END { print total/10 }' creation_time_parallel.txt)
  	reorganization_time=$(awk '{ total += $1; count++ } END { print total/10 }' reorganization_time_parallel.txt)
  	dictionary_time=$(awk '{ total += $1; count++ } END { print total/10 }' dictionary_time_parallel.txt)
   	# Getting the average memory
   	memory=$(awk '{ total += $1; count++ } END { print total/10 }' creation_ram_parallel.txt)

       echo "$i,$edges,$nb,$splittime,$creation_time,$reorganization_time,$dictionary_time,$memory">>average_results_parallel.csv
       > creation_time_parallel.txt  #empty file
       > reorganization_time_parallel.txt
       > dictionary_time_parallel.txt
       > creation_ram_parallel.txt  #empty file

        #logging the resukts in historical file
        cat average_results_parallel.csv >> average_results_all_parallel.txt
        echo "end of $file_name"
        ###########################################################
   done

done