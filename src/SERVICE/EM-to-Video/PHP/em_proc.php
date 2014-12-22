<html>
<body>

<?php
if($_REQUEST['startx'] >= 0){
      //download data
      $startx = $_REQUEST['startx'] ;
      $endx = $_REQUEST['endx'] ;
      $starty = $_REQUEST['starty'] ;
      $endy = $_REQUEST['endy'] ;

   //exec('echo '.$startx." > tmp.txt");
   //exec('echo '."here > tmp.txt");
   exec('/bin/sh '."/var/www/html/GanitaBrain/PHP/hadoop-stream-ocp.sh ".$startx." ".$endx." ".$starty." ".$endy." >> stream-logs");
  }
 else
   {
     echo "<h1>Please fill out entire form and click button.</h1>";
   }

?>

</body>
</html> 
