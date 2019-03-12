<?php  

     $to = $_REQUEST["to"];
     $from = $_REQUEST["from"];
     $message = $_REQUEST["message"];
     $subject = $_REQUEST["subject"];
     $headers = "From: $from";  
     mail($to , $subject, $message ,$headers );
?>