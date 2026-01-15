import System.Directory (doesDirectoryExist, getDirectoryContents, removeFile)
import System.FilePath ((</>), takeExtension)
import Control.Monad (forM, mapM_)

-- deletes all non .hs files in this dir
main :: IO () 
main = getPaths "." >>= removeNotHs >> putStrLn "Finished deleting junk files"

getPaths :: FilePath -> IO [FilePath]
getPaths path = do
    entries <- getDirectoryContents path
    -- Filter out the special entries
    let entries' = filter (\s -> s /= "." && s /= "..") entries
    paths <- forM entries' $ \name -> do
        let fullPath = path </> name
        isDir <- doesDirectoryExist fullPath
        if isDir
            then getPaths fullPath
            else return [fullPath]
    return (concat paths)

removeNotHs :: [FilePath] -> IO ()
removeNotHs paths = mapM_ removeFile nonHs
    where nonHs = filter (\file -> takeExtension file /= ".hs") paths