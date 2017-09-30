from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction import DictVectorizer

def departit(original_tuple_array):
    x,y = zip(*original_tuple_array)
    return list(x),list(y)


def vectorize(feature):
    vectorizer = DictVectorizer(dtype=float, sparse=True)
    feature = vectorizer.fit_transform(feature)
    return feature


def label(target):
    encoder = LabelEncoder()
    return encoder.fit_transform(target)