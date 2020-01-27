#coding=utf8
# ========================================================
#   Copyright (C) 2020 All rights reserved.
#   
#   filename : format_label_kmeans_result.py
#   author   : malele@360.cn
#   date     : 2020-01-19
#   desc     : 
# ======================================================== 

import sys
import json


def parse_kmeans_result(filename):
    fd = open(filename, "r")
    data = fd.readlines()
    fd.close()
    dt = {}
    for line in data:
        line = line.strip().split("\t")
        if len(line) != 2: continue

        label, cluster_id = line
        if "_" in label:
            label = label.split("_")[-1]

        if cluster_id not in dt:
            dt[cluster_id] = [label]
        else:
            dt[cluster_id].append(label)

    for cluster_id, label_list in dt.items():
        num = len(label_list)
        label = ",".join(label_list)
        dt[cluster_id] = [num, label]
    return dt


f1 = "../data/itag_kmeans_result"
cluster_dt = parse_kmeans_result(f1)
cluster_dt_sorted = sorted(cluster_dt.items(), key=lambda d:d[1][0], reverse=True)

for cluster_id, info in cluster_dt_sorted:
    num = str(info[0])
    label = info[1]
    out = [cluster_id, num, label]
    print "\t".join(out)


