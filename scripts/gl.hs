import System.Directory (doesDirectoryExist, getDirectoryContents)
import System.FilePath ((</>))
import Control.Monad (forM)

-- Prints the line count of everythibg in src/
main :: IO ()
main = getPaths "../src" >>= lineCount >>= print 

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

lineCount :: [FilePath] -> IO Int
lineCount paths = do
    counts <- forM paths $ \path -> do
        contents <- readFile path
        return $ length (lines contents)
    return (sum counts)