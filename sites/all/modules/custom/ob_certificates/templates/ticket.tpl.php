<style>
  .membrete {
      width: 100%;
      height: 700px;
      margin: 1em auto;
      position: relative;
  }
  .campo-text {
      position: absolute;
      width: 90%;
      top: 50px;
      height: 605px;
      left: 5%;
  }
  p {
      font-family: arial, helvetica, sans-serif;
      font-size: 12px;
      color: #333;
  }
  table {
      font-family:"Gill Sans", "Gill Sans MT", "Myriad Pro", "DejaVu Sans Condensed", Helvetica, Arial, sans-serif;
  }
  thead {
      padding-bottom: 0.5em;
      margin-bottom: 0.5em;
      border-bottom: 1px solid #DDD;
  }
  tr td {
    border: 1px solid #DDD;
    padding: 0.5em;
  }
</style>
<div id="s_content" class="membrete">
    <table width="100%">
      <tr>
        <td>Empresa:</td>
        <td><?php print $cabeza['ID_EMP'].' '.$cabeza['DESCRIPCION']; ?></td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>Pagina <span>1</span></td>
      </tr>
      <tr>
          <td>Documento</td>
          <td><?php print $detalle[0]['LAPSO_DOC'] . ' '. $cabeza['ID_EMP']; ?> PL-098765</td>
          <td>Prediodo de Liquidacion</td>
          <td><?php print $detalle[0]['FECHA_INICIAL']?></td>
          <td>AL <?php print $detalle[0]['FECHA_FINAL']?></td>
      </tr>
    </table>
    <table width="100%">
      <tr>
          <td>Codigo</td>
          <td><?php print $cabeza['ID_TERC']?></td>
          <td><?php print $cabeza['NOMBRE_COMPLETO']?></td>
          <td>Cargo</td>
          <td><?php print $cabeza['CARGO']?></td>
          <td>&nbsp;</td>
          <td>&nbsp;</td>
      </tr>
        <tr>
          <td>Costo</td>
          <td><?php print $cabeza['ID_CCOSTO']?></td>
          <td><?php print $cabeza['CENTRO_COSTO']?></td>
          <td>C.U.</td>
          <td><?php print $cabeza['ID_CO'].' '.$cabeza['CENTRO_OPERACION']; ?></td>
          <td>Tipo Nomina</td>
          <td><?php print $cabeza['ID_TIPO_NOMINA'].' '.$cabeza['TIPO_NOMINA']; ?></td>
      </tr>
      <tr>
          <td>Banco</td>
          <td><?php print $cabeza['BANCO']?></td>
          <td>BANCOLOMBIA</td>
          <td>&nbsp;</td>
          <td>&nbsp;</td>
          <td>Cuenta de Ahorros No.</td>
          <td><?php print $cabeza['CUENTA']?></td>
      </tr>
    </table>
    <table width="100%">
      <tr>
          <th width="10%" scope="col">Concepto</th>
          <th width="30%" scope="col">Descripcion</th>
          <th width="20%" scope="col">Cant/horas</th>
          <th width="20%" scope="col">Vlr. Devengado</th>
          <th width="20%" scope="col">Vlr. Deduccion</th>
          
      </tr>
      <?php foreach ($detalle as $key => $value) { ?>
        <tr>
          <td style="text-align: center"><?php print $value['ID_CPTO']; ?></td>
          <td><?php print $value['DESCRIPCION'];?></td>
          <td><?php print number_format(trim($value['NMMOV_HORAS'])); ?></td>
          <td style="text-align: right"><?php print number_format(trim($value['DEVENGO']), 2); ?></td>
          <td style="text-align: right"><span style="text-align: right"><?php print number_format(trim($value['DEDUCCION']), 2); ?></span></td>
          
        </tr>
      <?php }?>
    </table>
    <table width="100%">
      <tr style="padding-bottom:0.5em, margin: 0.5em 0, border-bottom: 1px solid #333">
          <td>&nbsp;</td>
          <td>&nbsp;</td>
          <td>Devengo</td>
          <td>Deduccion</td>
          <td>Neto a Pagar</td>
      </tr>
        <tr>
          <td>TOTALES</td>
          <td style="text-align: right"><?php print $totales['total_horas']?></td>
          <td style="text-align: right"><?php print number_format(trim($totales['devengo']), 2) ?></td>
          <td style="text-align: right"><?php print number_format(trim($totales['deduccion']), 2) ?></td>
          <td style="text-align: right"><?php print number_format(trim($totales['neto']), 2) ?></td>
      </tr>
    </table>
    <table width="100%">
      <tr>
        <td width="7%">CC:</td>
        <td width="93%"><?php print $cabeza['ID_TERC']?></td>
      </tr>
    </table>
</div>
