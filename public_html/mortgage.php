<html>
<head>
    <link rel="stylesheet" type="text/css" href="assign04.css">
<title>Mortgage Calculator</title>
</head>
<body>
<?php
          $c1 = $_GET["APR"];
          $n1 = $_GET["LoanTerm"];
          $LoanAmount1 = $_GET["LoanAmount"];
          $c = $c1 / 1200;
          $n = $n1 * 12;
    // Calculate (1 + $c )^$n portion of formula
           $num = 1 + $c;
          $power = pow($num, $n);
    // LoanAmount 
          $LoanAmount = $LoanAmount1 * (($c * $power) / ($power - 1));
          $LoanAmount = round($LoanAmount, 2);
     print "<div class=\"box text\"><div class=\"sidemargin\"><h1>APR: $c1</h1><h1>Loan Amount: $LoanAmount1</h1><h1>Loan Term: $n1</h1><h1><b>Monthly Payment: $LoanAmount</b></h1></div></div>";
?>
</body>
</html>
      <!--$LoanAmount = $LoanAmount.toFixed(2);-->
      
      <!--    document.getElementById("monthlypayment").value = $LoanAmount;-->
