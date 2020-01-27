#coding=utf8
import sklearn
from sklearn.datasets.samples_generator import make_blobs

data, label = make_blobs( n_samples = 2000,
                   n_features = 2, 
                   centers=[[-1,-1], [0,0], [1,1], [2,2]], 
                   cluster_std = [0.4, 0.3, 0.2, 0.5],
                   random_state = 1)

for i in range(len(label)):
    key = label[i]
    val = list(data[i,:])
    val = [str(round(x,5)) for x in val]
    out = [str(key)] + val
    print "\t".join(out)

