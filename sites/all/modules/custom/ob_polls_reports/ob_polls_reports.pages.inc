<?php
/*
 * Display the poll's results for users with appropriate permissions
 */
function ob_polls_reports_results_page($node) {
  $data = advpoll_get_data($node);
  $content = array();

  if ($node) {
    $content = ob_polls_reports_display_results($node->nid, $data);
  }

  return $content;
}

/*
 * Generate de results pdf
 */
function ob_polls_reports_results_page_pdf($node) {
  $data = advpoll_get_data($node);
  module_load_include('php', 'ob_polls_reports', 'includes/tcpdf/tcpdf');
  class MYPDF extends TCPDF {

    //Page header
    public function Header() {
        // Logo
        $image_file = drupal_get_path('module', 'ob_polls_reports') . '/header-lasante.jpg';
        $this->Image($image_file, -10, '', 250, '', 'JPG', '', 'T', false, 300, '', false, false, 0, false, false, false);
    }

    // Page footer
    public function Footer() {
        // Position at 15 mm from bottom
        $this->SetY(-15);
        // Set font
        $this->SetFont('helvetica', 'I', 8);
        $this->Cell(0, 15, "Calle 17A No. 32-34 - Tels: (57-1) 364 75 00 Fax: (57-1) 364 75 00 A.A. 10491 Bogotá D.C - Colombia", 0, false, 'C', 0, '', 0, false, 'M', 'M');
        $this->SetY(-10);
        $this->Cell(0, 15, "Linea de Servicio al Cliente 01 8000 110028 Pagina web: www.lasante.com", 0, false, 'C', 0, '', 0, false, 'M', 'M');
    }
  }
  $pdf = new MYPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, TRUE, 'UTF-8', FALSE);
  $pdf->SetHeaderMargin(0);
  $pdf->setFontSubsetting(TRUE);
  $pdf->SetFont('dejavusans', '', 14, '', TRUE);
  $pdf->AddPage();
  // CSS File
  $css_url = drupal_get_path('module', 'ob_polls_reports') . '/css/pdf-report-style.css';
  $css_file = array(
    '#type' => 'html_tag',
    '#tag' => 'style',
    '#value' => file_get_contents($css_url),
  );
  $title = array(
    '#type' => 'html_tag',
    '#tag' => 'h3',
    '#value' => $node->title,
    'attributes' => array(
      'class' => array(drupal_html_class('ob-polls-reports-table-title')),
    ),
  );
  $content = ob_polls_reports_display_results($node->nid, $data, FALSE);
  $title = render($css_file) . render($title);
  $html = render($css_file) . render($content);
  $content_with_image = ob_polls_reports_display_results($node->nid, $data);
  $chart_url = $content_with_image['chart']['#attributes']['src'];
  // Print text using writeHTML()
  $pdf->SetY(40);
  $pdf->writeHTML($title, true, false, true, false, '');
  $pdf->SetY(47);
  $pdf->Image($chart_url, '', '', 180);
  $pdf->SetY(140);
  $pdf->writeHTML($html, true, false, true, false, '');
  // This method has several options, check the source code documentation for more information.
  $pdf->Output($node->title . '.pdf', 'FD');
}

/*
 * Generate de results excel
 */
function ob_polls_reports_results_page_xls($node) {
  drupal_add_http_header('Content-Type', 'application/vnd.ms-excel;name="excel"');
  drupal_add_http_header('Content-Disposition', 'filename=' . $node->title . '.xls');
  drupal_add_http_header('Pragma', 'no-cache');
  drupal_add_http_header('Expires', '0');
  $data = advpoll_get_data($node);
  $content = ob_polls_reports_display_results($node->nid, $data);
  $content['chart']['#attributes']['width'] = 583;
  $content['chart']['#attributes']['height'] = 340;
  echo utf8_decode(render($content));
}

/*
 * Determine how to theme poll results 
 */
function ob_polls_reports_display_results($nid, $data, $image = TRUE) {
  $content = array();
  $choiceSet = array();
  $votes = advpoll_get_votes($nid, $data->behavior);

  // Array of poll choices
  foreach ($data->choices as $choice) {
    if ($choice['write_in']) {
      $choiceSet[$choice['choice_id']] = $choice['choice'] . ' ' . t('(Write-in)');
    }
    else {
      $choiceSet[$choice['choice_id']] = $choice['choice'];
    }
  }

  // Generating image chart
  if ($image) {
    $chart_type = 'p3';
    $chart_size = '650x300';
    $chart_data_array = array();
    $chart_labels_array = array();

    foreach ($votes['choices'] as $key => $choice) {
      $chart_data_array[] = $choice['percentage'];
      $chart_labels_array[] = $choiceSet[$choice['index']] . ' - ' . $choice['percentage'] . '%';
    }
    $chart_data = implode(',', $chart_data_array);
    $chart_data = implode(',', $chart_data_array);
    $chart_labels = implode('|', $chart_labels_array);
    $content['chart'] = array(
      '#type' => 'html_tag',
      '#tag' => 'img',
      '#value' => '',
      '#attributes' => array(
        'src' => $url = url('https://chart.googleapis.com/chart', array(
          'query' => array(
            'cht' => $chart_type,
            'chs' => $chart_size,
            'chd' => 't:' . $chart_data,
            'chl' => $chart_labels,
          ),
        )),
        'width' => 600,
        'height' => 350,
        'border' => 0,
        // 'src' => 'https://chart.googleapis.com/chart?cht=' . $chart_type . '&chs=' . $chart_size . '&chd=t:' .$chart_data . '&chl=' . $chart_labels,
      ),
    );
  }

  // Generating table
  $table_header = array(
    array('data' => t('Choice'), 'class' => 'ob-polls-reports-table-header'),
    array('data' => t('Votes'), 'class' => 'ob-polls-reports-table-header'),
    array('data' => t('Percentage'), 'class' => 'ob-polls-reports-table-header'),
  );
  $table_rows = array();
  foreach ($votes['choices'] as $key => $choice) {
    $row = array();
    $row[] = $choiceSet[$choice['index']];
    $row[] = $choice['votes'];
    $row[] = $choice['percentage'];
    $table_rows[] = $row;
  }
  $table = array(
    'header' => $table_header,
    'rows' => $table_rows,
    'attributes' => array(
      'class' => array(drupal_html_class('ob-polls-reports-table')),
      'cellpadding' => '4',
    ),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => FALSE,
    'empty' => t('There are no votes'),
  );
  $content['table'] = array(
    '#markup' => theme_table($table),
  );

  
  return $content;
}

/**
 * Select poll form
 */
function ob_polls_reports_form($form, &$form_state) {
  $polls = array();
  $export_types = array(
    'pdf' => 'PDF',
    'xls' => 'Excel',
  );
  $polls_query = new EntityFieldQuery();
  $polls_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'advpoll')
    ->addMetaData('account', user_load(1)); // Run the query as user 1.
  $polls_result = $polls_query->execute();
  if (isset($polls_result['node'])) {
    foreach ($polls_result['node'] as $key => $poll) {
      $node = node_load($key);
      $polls[$node->nid] = $node->title;
    }
  }
  if ($polls) {
    $form['poll'] = array(
      '#type' => 'select',
      '#title' => t('Poll'),
      '#options' => $polls,
      '#required' => TRUE,
    );
    $form['export_as'] = array(
      '#type' => 'select',
      '#title' => t('Export as'),
      '#options' => $export_types,
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Generate'),
    );
  }
  else {
    $form['no_polls'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#value' => t('There are no polls'),
      '#attributes' => array(
        'class' => array('no-polls-message'),
      ),
    );
  }
  return $form;
}

/**
 * Select poll form submit
 */
function ob_polls_reports_form_submit($form, &$form_state) {
  $nid = $form_state['values']['poll'];
  $type = $form_state['values']['export_as'];
  if ($type == 'xls') {
    $form_state['redirect'] = 'poll/' . $nid . '/results.xls';
  }
  else {
    $form_state['redirect'] = 'poll/' . $nid . '/results.pdf';
  }
}