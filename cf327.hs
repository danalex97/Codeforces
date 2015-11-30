import Control.Applicative
import Control.Monad
import Data.Maybe

splitAll :: [Int] -> [[Int]]

splitAll []    
  = [[]]
splitAll [x]   
  = [[x]]
splitAll [x,y]
  | x == y = [[x],[y]]
  | x /= y = [[x,y]]
splitAll (x:y:xs)
  | x == y && null rest = [x] : [[y]]
  | x == y              = [x] : rest 
  | otherwise           = (x : h) : t
  where 
    rest  = splitAll (y:xs)
    (h:t) = rest

change :: [Int] -> [Int]
change xs
  | n < 3  = xs 
  | odd  n = arrOf (n-1) ft ++ [lt] 
  | even n = arrOf hn ft ++ arrOf hn lt
  where 
    n  = length xs
    hn = n `div` 2
    ft = head xs 
    lt = last xs
    
    arrOf l v
      = take l $ repeat v
 
solve :: [Int] -> (Int,[Int])
solve xs 
  = ( ans, concat arr' )
  where 
    ans = ( maximum (map length arr) - 1 ) `div` 2
    arr  = splitAll xs
    arr' = map change arr

output :: (Int,[Int]) -> String
output (x, xs) = show x ++ "\n" ++ ( concat $ map (++ " ") (map show xs) )  

main = ( output . solve . map ( read :: String -> Int ) . words . last . lines) <$> getContents >>= putStrLn

 
