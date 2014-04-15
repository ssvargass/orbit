<h3 class="cer_titulo"><br><br><br><br><?php print $personal['NOMBRE_EMPRESA'] ?></h3>
<h3 class="cer_titulo2">CERTIFICA QUE</h3>
<p>La señora <?php print $personal['NOMBRE_COMPLETOS'] ?> indentificada con cedula 
de ciudadanía No. <?php print $personal['EMPLEADO'] ?>
Labora en esta compañía desde el  <?php print $personal['dia'] ?> 
de  <?php print $personal['mes'] ?> de  <?php print $personal['ano'] ?> con un contrato de trabajo a 
<?php print $personal['TIPO_CONTRATO'] ?> desempeñando en la actualidad el cargo de 
<?php print $personal['NOMBRE_CARGO'] ?> con un salario básico menusal 
<?php print $personal['salario_letr'] ?> (<?php print $personal['salario_num'] ?>). Y un salario promedio 
variable de <?php print $personal['var_letr'] ?> (<?php print $personal['var_num'] ?>).
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