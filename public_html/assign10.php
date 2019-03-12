<!DOCTYPE html>
<!-- assign10.php - displays a confirmation page of items selected -->
<html lang = "en">
   <head>
     <title>Flower Shop Validation Form</title>
     <meta charset = "utf-8">
     <link rel="stylesheet" type="text/css" href="assign05.css">
   </head>    
  <body>
  

     <?php
        //Get personal information values

        $firstName = $_GET["fbyname"];
        $lastName = $_GET["lname"];
        $address = $_GET["address"];
        $phone = $_GET["phoneNum"];
        $cardType = $_GET["CardType"];
        $month = $_GET["month"];
        $monthArray = array("01" => "January", "02" => "February", "03" => "March","04"=> "April", "05" => "May","06" =>"June","07"=>"July","08"=>"August",
                             "09"=>"September", "10"=>"October","11"=>"November","12"=>"December");
        $monthString = $monthArray["$month"];
        $year = $_GET["year"];

      //get the array for selected items
        $itemsArray = $_GET["flower"];
  
      //get the array for quantity values
        $qty = $_GET["qty"];
   
    //Create the array of the prices called sum, and use the selected items values as the key to map to the price in priceArray and
    //  the quantity in quantityMapArray.
      $sum = $_GET["some"];
      $priceArray = array("Rose" => "$sum[0]", "Petuna" => "$sum[1]", "Daisy" => "$sum[2]", "Blue" => "$sum[3]", "White" => "$sum[4]");
      $quantityMapArray = array("Rose" => "$qty[0]", "Petuna"=>"$qty[1]", "Daisy"=>"$qty[2]", "Blue"=>"$qty[3]", "White" => "$qty[4]");     
    $total = 0;
     while($item = each($itemsArray)) {
          $product = $item["value"];
           $quantity = $quantityMapArray[$item["value"]];
           $itemTotal = $priceArray[$item["value"]] * $quantity;
           $total = $total + $itemTotal;
     }
  //reset the pointer of $itemsArray back to the first element
     reset($itemsArray);         

  //build the html string that will create a table once printed using the aggregated values.
      $list = "<table border='3' id='store'><tr><th>Product</th><th>Quantity</th><th>Price</th></tr>";
                   while($item = each($itemsArray)) {
                           global $list;
                            $product1 = $item["value"];
                            $quantity = $quantityMapArray[$item["value"]];
                            $price1 = $priceArray[$item["value"]] * $quantity;
                            $list = $list . "<tr><td>$product1</td><td>$quantity</td><td>$$price1</td></tr>";
                  }
                   $list = $list . "<tr><td></td><td>Your Total is</td><td>$$total</td></tr>";
   ?>

   <!-- Display buyer's information  -->
  <h1 class="title">Order Validation Form</h1>
  <div class="form">
    <p>Order for: <?php print ("$firstName $lastName"); ?></p>
    <p>Address: <?php print ("$address"); ?></p>
    <p>Phone Number: <?php print ("$phone"); ?></p>
    <p>Payment Method Type: <?php print ("$cardType");?></p>
    <p>Expiration Month: <?php print ("$monthString");?></p>
    <p>Expiration Year: <?php print ("$year");?></p>
     </div>
  <!-- Display what the user is buying -->
     <div>
         <?php 
                    print("$list");
         ?>
     </div>
    

  <!-- Have the user confirm or cancel the transaction -->
   <form action="assign10_a.php" method="get">
   <input type="submit" name="confirm" value="Confirm">
   <input type="submit" name="cancel" value="Cancel">
   </form>

  </body>
 
</html>
