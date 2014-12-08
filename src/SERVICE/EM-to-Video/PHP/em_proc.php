<html>
<body>

<?php
if (isset($_REQUEST['startx']))
  //if "email" is filled out, send email
  {
    if($_REQUEST['email'] != ""){
      //send email
      $email = $_REQUEST['email'] ;
      $subject = $_REQUEST['subject'] ;
      $message = $_REQUEST['message'] ;
      mail("terry@ganita.org", $subject,
	   $message, "From:" . $email);
      echo "<h2>Thank you for sending your email.</h2>";
      echo '<a href="http://www.ganita.org">Go Back to Ganita</a>';
    }
    else
      //if "email" is not filled out, display the form
      {
	echo "<h1>Please fill out email form and click send to send email.</h1>";
	echo "<form method='post' action='send_email.php'>
  Your Email: <input name='email' type='text' /><br />
  Subject: <input name='subject' type='text' /><br />
  Message:<br />
  <textarea name='message' rows='15' cols='40'>
  </textarea><br />
  <input type='submit' value='Send' />
  </form>";
      }
  }
 else
   //if "email" is not filled out, display the form
   {
     echo "<h1>Please fill out email form and click send to send email.</h1>";
     echo "<form method='post' action='send_email.php'>
  Your Email: <input name='email' type='text' /><br />
  Subject: <input name='subject' type='text' /><br />
  Message:<br />
  <textarea name='message' rows='15' cols='40'>
  </textarea><br />
  <input type='submit' value='Send' />
  </form>";
   }

?>

</body>
</html> 
