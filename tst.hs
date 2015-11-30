module Tst where 

elem'' :: Eq a => a -> [a] -> Bool
elem'' _ []     = False
elem'' x (y:ys) = x == y || elem'' x ys

elem' :: Eq a => a -> [a] -> Bool
elem' _ []     = False
elem' x (y:ys) = elem' x ys || x == y


