<strong><?php print $node->name ?> lo ha invitado a la reunion <?php print$node->title ?>.</strong>
<br>
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
Esta reunion ya fue aprobada por el web master.