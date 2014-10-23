<?php
/**
*@ file
* a new test
*/

/**
function doctor_menu() {
  $items = array();
 
  $items['doctors'] = array(
    'title' => t('Doctors'),
    'page callback' => 'doctors_list',
    'access arguments' => array('access doctor'),
    'type' => MENU_CALLBACK,
  );
 
  $items['doctors/delete/%doctor_user'] = array(
    'title' => t('Delete doctor'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('doctor_delete_confirm', 2),
    'access arguments' => array('access doctor'),
    'type' => MENU_CALLBACK,
  );
 
  return $items;
}
*/


function doctors_list() {
	$header = array(t('Doctor Name'), t('Gender'), t('Phone No.'), t('Status'), t('Action'));
 
	$query = "SELECT * FROM {doctor}";
	$rs = db_query($query);
 
	$row = array();
 
	if ($rs) {
		while ($data = db_fetch_object($rs)) {
			$gender = $data->gender == 'M' ? t('Male') : t('Female');
			$status = $doctor->status ? t('active') : t('inactive');
			$row[] = array(stripslashes($data->firstname) . ' ' . stripslashes($data->lastname), $gender, stripslashes($data->phoneno), $status, 
			"<a href='/doctors/edit/{$data->doctorid}'>" . t('Edit') . "</a> | <a href='/doctors/delete/{$data->doctorid}'>" . t('Delete') . "</a>");
		}
	}
 
	$str .= theme_table($header, $row);
 
	return $str;
}

function doctor_user_load($doctorid) {
	$query = "SELECT * FROM {doctor} WHERE doctorid = %d";
	$rs = db_query($query, $doctorid);
 
	if ($rs) {
		while ($data = db_fetch_object($rs)) {
			return $data;
		}
	}
 
	return FALSE;
}

function doctor_delete_confirm(&$form_state, $doctor) {
	$form['_doctor'] = array(
		'#type' => 'value',
		'#value' => $doctor,
	);
 
	return confirm_form($form,
    	t('Are you sure you want to delete this doctor?'),
    	isset($_GET['destination']) ? $_GET['destination'] : "doctors",
    	t('This action cannot be undone.'),
    	t('Delete'),
    	t('Cancel'));
}

function doctor_delete_confirm_submit($form, &$form_state) {
	$form_values = $form_state['values'];
 
	if ($form_state['values']['confirm']) {
		$doctor = $form_state['values']['_doctor'];
 
		doctor_delete($form_state['values'], $doctor->doctorid);			
 
		drupal_set_message(t('Doctor has been deleted successfully.'));
  	}
 
	drupal_goto("doctors");
}

