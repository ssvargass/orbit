<h3 class="cer_titulo"><br><br><br><br><?php print $personal['NOMBRE_EMPRESA'] ?></h3>
<h3 class="cer_titulo2">CERTIFICA QUE</h3>
<p>
<?php print $personal['antecede'] ?> <?php print $personal['NOMBRES_COMPLETOS'] ?> <?php print $personal['ident'] ?> con cedula de ciudadanía No. 
<?php print $personal['EMPLEADO'] ?> labora en esta compañía desde el <?php print $personal['dia'] ?> 
de <?php print $personal['mes'] ?> de  <?php print $personal['ano'] ?> 
desempeñando en la actualidad el cargo de <?php print trim($personal['NOMBRE_CARGO']) ?>, con
 un contrato de trabajo a <?php print $personal['TIPO_CONTRATO'] ?>, con un ingreso fijo mensual de 
 <?php print $personal['fijo_letr'] ?> (<?php print $personal['fijo_num'] ?>). Distribuidos en un sueldo básico ordinario de 
 <?php print $personal['salario_letr'] ?> (<?php print $personal['salario_num'] ?>), y otros beneficios de carácter no 
 salarial por <?php print $personal['flex_letr'] ?> (<?php print $personal['flex_num'] ?>).
</p>
<p>
La presente certificación se expide en la ciudad de Bogotá, a los <?php print $personal['act_dia'] ?> 
días del mes de <?php print $personal['act_mes'] ?> de <?php print $personal['act_ano'] ?>
<?php if(count($personal['to']) > 0): ?>
	, a peticion de <?php print $personal['to'] ?>
<?php endif; ?>
.
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