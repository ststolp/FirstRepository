<!DOCTYPE html>
<!-- assign10_a.php -displays confirmation or cancellation message -->
<html lang = "en">
   <head>
     <title>Confirmation</title>
     <meta charset = "utf-8">
     <link rel="stylesheet" type="text/css" href="assign05.css">
     
      
   </head>
  <body>
   <?php
       $confirm = $_GET["confirm"];
       $cancel = $_GET["cancel"];
       if($confirm){
          print("<h1 style='text-align:center'>Order confirmed!</h1>");
       }  else {
          print("<h1 style='text-align:center'>Order cancelled.</h1>");
       }



     ?>
     </body>

  </html>
