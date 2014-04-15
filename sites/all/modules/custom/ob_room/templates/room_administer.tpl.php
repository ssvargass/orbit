Se ha generado una nueva solicitud para la sala de reunión <?php print $node->sala->title?>
<br>
por favor ingrese al administrador de salas en Orbit para ver la solicitud.
<br>
Inicio: <?php print $node->field_fecha['und'][0]['value']; ?>
<br>
Fin: <?php print $node->field_fecha['und'][0]['value2']; ?>
<br>
Descripción: <?php print $node->field_descripci_n['und'][0]['value']; ?>
<br>
<?php if(count($node->invitados) > 0): ?>
Invitados:
<?php foreach ($node->invitados as $key => $value) { 
  print $value->name . '<br>';
}?>
<?php endif; ?>