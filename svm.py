import numpy as np
import json

model = json.load(open("linear_svm.json"))

def score(model, fv):    
    weights = np.array(model['weights'])
    bias = float(model['bias'])
    return weights.dot(fv.T) + bias

#print(score(model, np.array(model['weights'])))
data = []
with open('scores') as f:
    for l in f:
        if 'FEATURE VEC: ' in l:
            fv = np.array(list(map(float, l.replace('FEATURE VEC: ', '').split(','))))
        if 'SCORE: ' in l:
            _score = float(l.rstrip().replace("SCORE: ", '')) + float(model['bias'])
            print("Expected : " + str(_score))
            print("Predicted: " + str(score(model, fv)))
            data.append({
                "features": fv.tolist(),
                "score": _score
            })

with open("scores.json", "w") as w:
    json.dump({'tests': data}, w)