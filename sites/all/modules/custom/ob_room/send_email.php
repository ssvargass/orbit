<?php
function sendIcalEmail($nombre_dest,$apellido_dest,$email,$fecha_inicio,$evento_nombre,$fecha_fin,$evento_desc) {

 $nombre_from = "";//nombre para mostrar en el campo DE: $email_from = "";//tu@mail.com para el campo DE:
 $email_from = "";
 $subject = ""; //asunto del mail
 $evento_descripcion = $evento_desc; //Descripción del evento
 $meeting_location = ""; //Lugar donde se llevará a cabo el evento


//Convertimos la fecha de formato MYSQL (YYYY-MM-DD HH:MM:SS) a formato UTC (yyyymmddThhmmssZ)
 $meetingstamp = strtotime($fecha_inicio . " UTC");    
 $meetingstampb = strtotime($fecha_fin . " UTC");     
 $dtstart= gmdate("Ymd\THis\Z",$meetingstamp);
 $dtend= gmdate("Ymd\THis\Z",$meetingstampb);
 $todaystamp = gmdate("Ymd\THis\Z");

//Creamos identificador único aleatorio para el mensaje
 $cal_uid = date('Ymd').'T'.date('His')."-".rand()."ejemplo.com";

//Establecemos el formato del MIME 
 $mime_boundary = "----Meeting Booking----".md5(time());


 $module = 'notifications';
 $key = 'envio';
$language = language_default();
$params = array();
$from = NULL;
$send = FALSE;
$message = drupal_mail($module, $key, $email ,$language, $params, $from, $send);
$message['subject'] = $subject;
$message['headers']['Content-Type'] = "multipart/alternative; boundary=\"$mime_boundary\"\n";
$message['headers']['Content-class'] = "urn:content-classes:calendarmessage";

$message['body'] = array();

 $body = "--$mime_boundary\n";
 $body .= "Content-Type: text/html; charset=UTF-8\n";
 $body .=  "Content-Transfer-Encoding: 8bit\n\n";
 $body .=  "<html>\n";
 $body .= "<body>\n";
 $body .= '<p>Hola '.$nombre_dest.',</p>';
 $body .= "</body>\n";
 $body .= "</html>\n";
 $body .= "--$mime_boundary\n";

//$message['body'][] = $body;
//Ahora armamos los datos en formato iCalendar
 $ical =    'BEGIN:VCALENDAR
PRODID:-//Microsoft Corporation//Outlook 11.0 MIMEDIR//EN
VERSION:2.0
METHOD:PUBLISH
BEGIN:VEVENT
ORGANIZER:MAILTO:'.$email_from.'
DTSTART:'.$dtstart.'
DTEND:'.$dtend.'
LOCATION:'.$meeting_location.'
TRANSP:OPAQUE
SEQUENCE:0
UID:'.$cal_uid.'
DTSTAMP:'.$todaystamp.'
DESCRIPTION:'.$evento_descripcion.'
SUMMARY:'.$subject.'
PRIORITY:5
CLASS:PUBLIC
END:VEVENT
END:VCALENDAR';

$invitacion =   'Content-Type: text/calendar;name="meeting.ics";method=REQUEST\n';
$invitacion .= "Content-Transfer-Encoding: 8bit\n\n";
$invitacion .= $ical;
$message['body'][] = $body . $invitacion;
//Agregamos al cuerpo del mensaje la iCal
 //$message['body'][] =  'Content-Type: text/calendar;name="meeting.ics";method=REQUEST';
 //$message['body'][] =  "Content-Transfer-Encoding: 8bit";
 //$message['body'][] = $ical;
$system = drupal_mail_system($module, $key);


// Format the message body.
$message = $system->format($message);


// Send e-mail.
$message['result'] = $system->mail($message);
dpm($message);
}

/*$path = drupal_get_path('module', 'ob_polls_reports') . '/send_email.php';
include($path);
sendIcalEmail('sergop','vargas','sergio.svargass@gmail.com','2014-04-05 12:00:00','ejemplo','2014-04-05 13:00:00','ejemplo del evento')*/
?>