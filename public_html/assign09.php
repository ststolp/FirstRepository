<?php
     // create a PHP object with the filename,filetype, and cwd properties.
     class fileN
     {
         public $fileName;
         public $fileType;
         public $cwd;
     }

     $cwd = getcwd();
   //getcwd();     // get path to the current working directory
     $folder = ".";       // Set the folder variable to specify the "current" directory    
     
     // create an array of filenames of files from the current directory
     $files1 = scandir($folder);
     $directory = Array();     // create a array object to store a list of objects.
     $files = Array();

     /*******************************************************************************
     *  Start your PHP code here!
     *
     * Add code to populate the "$directory" array with a list of "fileN" objects.
     * Use "new fileN()" to create a fileN object.
     * Set each fileN object property to the appropriate values.
     * You can get each file name from the "$files" array.
     * You can get each file type by calling the php function "filetype()" passing it the filename.
     * The "filetype()" function returns the file type. The returned file type is either "file" or "dir".  
     * The current working directory has been stored in $cwd. 
     *****************************************************************/
    
    $len = sizeof($files1);
     for ($i = 0;$i < $len; $i++) {
         $obj = new fileN();
        $obj->fileName = $files1[$i];     
        $obj->fileType = filetype($obj->fileName);    
        $obj->cwd =  "/~sstolp/$obj->fileName";
         $directory[] = $obj;
      }
    
     
     
     /*******************End of your Code *******************************************/

     // convert the PHP array of objects to a JSON string
     $str = json_encode($directory);
     print "\n $str \n";   //output the json string - The string is sent to the browser.      
 ?>



