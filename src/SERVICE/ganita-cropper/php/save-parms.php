<html>
<body>

<?php
if($_REQUEST['dataX'] >= 0){
      //download data
      $datax = $_GET['dataX'];
      $datay = $_GET['dataY'];
      $dataw = $_GET['dataWidth'];
      $datah = $_GET['dataHeight'];
      $fileN = $_GET['fileName'];

      exec('echo convert '.$fileN.' -crop '.$dataw.'x'.$datah.'+'.$datax.'+'.$datay.' '.$fileN.'.crop_'.$dataw.'_'.$datah.'_'.$datax.'_'.$datay.'.png >> cropper.sh');
  }
 else
   {
     echo "<h1>Please fill out entire form and click button.</h1>";
   }

?>

</body>
</html> 
