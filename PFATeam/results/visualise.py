#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 28 23:46:47 2022

@author: ramizouari
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def visualise_time(profile,start_time, end_time,ax=None):
    if ax is None:
        fig,ax=plt.subplots()
    sns.scatterplot(data=profile,x="Time",y="Current Memory")
    

def load_dataset(csv_name:str):
    data= pd.read_csv(csv_name,sep='\t')
    data["Start Time"]=pd.to_datetime(data["Start Time"])
    data["End Time"]=pd.to_datetime(data["End Time"])
    return data
    
def load_profile(profile_name:str):
    data= pd.read_csv(profile_name)
    data["Time"]=pd.to_datetime(data["Time"])
    return data


dir_name="aws"
exp_name=dir_name
csv_name=dir_name+'/'+exp_name+"-parallel.tsv"
profile_name=dir_name+'/'+exp_name+"-parallel.profile"
dataset=load_dataset(csv_name)
profile=load_profile(profile_name)