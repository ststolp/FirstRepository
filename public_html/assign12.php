<?php
     /* assign12.php gets the data given from assign12.html. When write is equal to yes,
        we write to the file with the data embedded in html code (for a table) as a string
        When write is not equal to yes, get all the contents from the file and return the string back to the browser. 
      */
        $write = $_GET["write"];
        $fName = $_GET["firstName"];  
        $lName = $_GET["lastName"];
        $studentid = $_GET["studentId"];
        $performancetype = $_GET["performancetype"];
        $skilllevel = $_GET["skilllevel"];
        $instrument = $_GET["instrument"];
        $location = $_GET["location"];
        $room = $_GET["room"];
        $timeslot = $_GET["timeSlot"];
        $fName2 = $_GET["firstName2"];
        $lName2 = $_GET["lastName2"];
        $studentid2 = $_GET["studentId2"];
  $filename = "/home/sto15076/public_html/piano/piano4.txt";
          if ($write == "yes") {
              if ($performancetype != "duet") {
                 $new = "<tr><td>" . $fName . " " . $lName . "</td><td>" . $studentid . "</td><td>" . $performancetype . "</td><td>" . $skilllevel . "</td><td>" .  $instrument . "</td><td>" . $location . ", " . $room . "</td><td>" . $timeslot . "</td></tr>";
               } else {
                 $new = "<tr><td>" . $fName . " " . $lName . "</td><td>" . $studentid . "</td><td>" . $performancetype . "</td><td>" . $skilllevel . "</td><td>" . $instrument . "</td><td>" . $location . ", " . $room . "</td><td>" . $timeslot . "</td></tr><tr><td>" . $fName2 . " " . $lName2 . "</td><td>" . $studentid2 . "</td><td>" . $performancetype . "</td><td>" . $skilllevel . "</td><td>" . $instrument . "</td><td>" . $location . ", " . $room . "</td><td>" . $timeslot . "</td></tr>";
               }
                 $table = $new;
                
               file_put_contents($filename, $table, FILE_APPEND);
          } else {
              //read from file
          $string = file_get_contents($filename);
     print "$string";
         }       
?>
