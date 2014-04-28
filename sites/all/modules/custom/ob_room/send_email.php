<?php

function sendCalEntry(){
 	$tsStart = '2014-04-11 12:00:00';
 	$tsEnd = '2014-04-11 13:00:00';
 	$location = '';
 	$summary = '';
 	$title = 'Ejemplo';
 	$resources = '';
 	$to = 'sergio.svargass@gmail.com';
 	$subject = 'ejemplo envio 1';
	
	$meetingstamp = strtotime($tsStart . " COT");    
	$meetingstampb = strtotime($tsEnd . " COT");     
	$dtstart= gmdate("Ymd\THis\Z",$meetingstamp);
	$dtend= gmdate("Ymd\THis\Z",$meetingstampb);
	$todaystamp = gmdate("Ymd\THis\Z");
	$loc = $location;

	/*$vcal = "BEGIN:VCALENDAR\r\n";
	$vcal .= "VERSION:2.0\r\n";
	$vcal .= "PRODID:-//nonstatics.com//OrgCalendarWebTool//EN\r\n";
	$vcal .= "METHOD:REQUEST\r\n";
	$vcal .= "BEGIN:VEVENT\r\n";
	$vcal .= "ORGANIZER;CN=\"".'LASANTE'." (".'usuariopreuba'.")"."\":mailto:".'orbit@lasante.com.co'."\r\n";
	$vcal .= "UID:".date('Ymd').'T'.date('His')."-".rand()."-nonstatics.com\r\n";
	$vcal .= "DTSTAMP:".date('Ymd').'T'.date('His')."\r\n";
	$vcal .= "DTSTART:$dtstart\r\n";
	$vcal .= "DTEND:$dtend\r\n"; 
	$vcal .= "LOCATION:$location\r\n";
	$vcal .= "SUMMARY:$summary\r\n";
	$vcal .= "DESCRIPTION:Hinweis/Fahrer:$summary - Folgende Resourcen wurden gebucht: $resources \r\n";
	$vcal .= "BEGIN:VALARM\r\n";
	$vcal .= "TRIGGER:-PT15M\r\n";
	$vcal .= "ACTION:DISPLAY\r\n";
	$vcal .= "DESCRIPTION:Reminder\r\n";
	$vcal .= "END:VALARM\r\n";
	$vcal .= "END:VEVENT\r\n";
	$vcal .= "END:VCALENDAR\r\n";*/

	$vcal = "BEGIN:VCALENDAR
PRODID:-//Drupal//iCal file//EN
VERSION:2.0
METHOD:PUBLISH
BEGIN:VEVENT
UID:" . date('Ymd').'T'.date('His')."-".rand()."-nonstatics.com\r\n".
"DTSTAMP:".date('Ymd').'T'.date('His')."\r\n".
"DTSTART:" . $dtstart ."\r\n".
"DTEND:". $dtend ."\r\n".
//%node-ical-rrule
"SUMMARY:". $summary ."\r\n".
"DESCRIPTION:Hinweis/Fahrer:$summary - Folgende Resourcen wurden gebucht: $resources \r\n".
//"URL:"%node-ical-url
//"CREATED:"%node-ical-created
//"LAST-MODIFIED:"%node-ical-last-modified
"END:VEVENT
END:VCALENDAR";
 

	$module = 'notifications';
	$key = 'envio';
	$language = language_default();
	$params = array();
	$from = NULL;
	$send = FALSE;

	$message = drupal_mail($module, $key, $to ,$language, $params, $from, $send);

	/*$message['subject'] = $subject;
	$message['headers']['Content-Type'] = 'text/calendar';
	$message['headers']['name'] = 'calendar.ics';
	$message['headers']['method'] = 'REQUEST';
	$message['headers']['charset'] = 'UTF-8';
	$message['headers']['Content-Transfer-Encoding'] = '8bit';
	$message['headers']['X-Mailer'] = 'Microsoft Office Outlook 12.0';*/
	$filename = 'calendar.ics';

	$boundary = '------------'. md5(uniqid(time()));

    $message['headers']['Content-Type'] = 'multipart/mixed; boundary="'. $boundary .'"';
    unset($message['headers']['Content-Transfer-Encoding']);

    $body = "\n--". $boundary ."\n".
      "Content-Type: text/plain; charset=UTF-8; format=flowed; delsp=yes\n".
      "Content-Transfer-Encoding: 8bit\n\n";
      
    //$body .= is_array($message['body']) ? drupal_wrap_mail(implode("\n\n", $message['body'])) : drupal_wrap_mail($message['body']);
    $body = 'ejemplo';  
    $message['body'] = $body;
    $message['body'] .= "\n\n--". $boundary ."\n";
    $message['body'] .= "Content-Type: text/calendar; name=\"$filename\"\n";
    $message['body'] .= "Content-Transfer-Encoding: base64\n";
    $message['body'] .= "Content-Disposition: attachment; filename=\"$filename\"\n\n";
    $message['body'] .= chunk_split(base64_encode($vcal));
    $message['body'] .= "\n\n";
    $message['body'] .= "--". $boundary ."--";





	//$message['body'] = array();

	//$message['body'][] = $vcal;
	$system = drupal_mail_system($module, $key);


	// Format the message body.
	//$message = $system->format($message);


	// Send e-mail.
	$message['result'] = $system->mail($message);
	dpm($message);

}

/*$path = drupal_get_path('module', 'ob_polls_reports') . '/send_email.php';
include($path);
sendIcalEmail('sergop','vargas','sergio.svargass@gmail.com','2014-04-05 12:00:00','ejemplo','2014-04-05 13:00:00','ejemplo del evento')*/
?>