<h3>LABORATORIOS LA SANTE S.A.</h3>
<h3>CERTIFICA QUE</h3>
<p>
La señora <?php print $personal['NOMBRE_COMPLETO'] ?> indentificada con cedula de ciudadanía No. 
<?php print $personal['EMPLEADO'] ?> labora en esta compañía desde el <?php print $personal['dia'] ?> 
de  <?php print $personal['mes'] ?> de  <?php print $personal['ano'] ?>
desempeñando en la actualidad el cargo de <?php print $personal['NOMBRE_CARGO'] ?>, con
 un contrato de trabajo a termino indefinido, con un ingreso fijo mensual de XXXXXXXXXXXXXXX
 . Distribuidos en un salario integral de XXXXXXXXXX, y otros beneficios de carácter no 
 salarial por XXXXXXXXXX.
</p>
<p>
La presente certificación se expide en la ciudad de Bogotá, a los <?php print $personal['act_dia'] ?>
días del mes de <?php print $personal['act_mes'] ?> de <?php print $personal['act_ano'] ?>
</p>
<p>
	<?php print $personal['firma'] ?>
	<br>
	<?php print $personal['firma_nom'] ?>
	<br>
	<?php print $personal['firma_cargo'] ?>
	<br>
	<?php print $personal['firma_addi'] ?>
</p>