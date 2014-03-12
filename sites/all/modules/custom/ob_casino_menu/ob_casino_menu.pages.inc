<?php
/**
 * @file
 * Pages Casino menu.
 */

/**
 * Callback for special menu page
 */
function ob_mc_special_menu_page() {
	$content = array();
	// Select meteting form
	$content['form'] = drupal_get_form('ob_mc_select_meeting_form');
	$content['form']['#access'] = TRUE;

	// Assingned special menus
	$casino_special_menu_query = new EntityFieldQuery();
  $casino_special_menu_query->entityCondition('entity_type', 'casino_special_menu')
    ->addMetaData('account', user_load(1)); // Run the query as user 1.
  $casino_special_menu_result = $casino_special_menu_query->execute();

  $content['assingned_special_menus'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Assingned special menus'),
  	'#weight' => 5,
  	'#collapsible' => FALSE,
  	'#collapsed' => FALSE,
  );
  if ($casino_special_menu_result['casino_special_menu']) {
  	foreach ($casino_special_menu_result['casino_special_menu'] as $key => $value) {
  		$casinospecialmenu = casinospecialmenu_load($key);
  		$meeting = node_load($casinospecialmenu->meeting);
  		$content['assingned_special_menus'][$key] = array(
  			'#type' => 'container',
  			'#attributes' => array(
					'class' => array('assigned-meeting', drupal_html_class('assigned-meeting-' . $key)),
				),
				'#access' => _casinospecialmenuentity_entity_view_access_callback($meeting),
  		);
  		$content['assingned_special_menus'][$key]['title'] = array(
				'#type' => 'html_tag',
				'#tag' => 'h3',
				'#value' => $meeting->title,
				'#weight' => -10,
			);
			$content['assingned_special_menus'][$key]['menu'] = field_view_field('casino_special_menu', $casinospecialmenu, 'field_menu_casino', 'full');
			$content['assingned_special_menus'][$key]['edit_link'] = array(
				'#markup' => l(t('Edit'), 'admin/casino-special-menu/manage/' . $key, array(
					'attributes' => array(
						'class' => array('edit-link'),
					),
					'query' => array(
						'destination' => current_path(),
					),
				)) 
			);
  	}
  }
	return $content;
}

/**
 * Select Meeting form
 */
function ob_mc_select_meeting_form($form, &$form_state) {
	$meetings = ob_cm_get_meetings(TRUE, TRUE);
	if ($meetings) {
		$form['meeting'] = array(
	    '#type' => 'select',
	    '#title' => t('Meeting'),
	    '#options' => $meetings,
	  );
	  $form['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('Config meeting menu'),
	  );
	}
	else {
		$form['no_meetings'] = array(
			'#type' => 'html_tag',
			'#tag' => 'div',
			'#value' => t('There are no future meetings to configure'),
			'#attributes' => array(
				'class' => array('no-meetings-message'),
			),
		);
	}
  return $form;
}

/**
 * Select Meeting form submit
 */
function ob_mc_select_meeting_form_submit($form, &$form_state) {
	$form_state['redirect'] = array(
	  'admin/casino-special-menu/add',
	  array(
	    'query' => array(
	      'meeting' => $form_state['values']['meeting'],
	      'destination' => current_path(),
	    ),
	  ),
	);
}