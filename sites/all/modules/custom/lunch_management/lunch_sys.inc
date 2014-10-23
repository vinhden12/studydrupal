<?php
/**
* @ file
* some report
*/

function report_form() {
	//$query = “SELECT p.*, UNIX_TIMESTAMP(p.create_date) AS create_date, c.name FROM {product} p LEFT JOIN {category} c ON p.cid = c.cid
	//WHERE p.status = 1 ORDER BY p.product_name”;

      $query = db_select('tbl_lunch', 't');
    //$query->fields('t', array('fid', 'fitem', 'fdescript','price','fimage'));
    $query->fields('t', array('foodid','uid', 'fitem', 'fdescript','price','fimage'));
    $query->condition('uid',$user->uid);
    $rs = db_query($query);
 
	$featured_products = featured_product();
	$status = array();
 
	if ($rs) {
		while ($data = db_fetch_object($rs)) {
            $options[$data->productid] = ”;
 
            $form[$data->productid]['name'] = array(’#value’ => stripslashes($data->product_name));
            $form[$data->productid]['category'] = array(’#value’ => stripslashes($data->name));
            $form[$data->productid]['discount'] = array(’#value’ => $data->discount . ‘%’);
            $form[$data->productid]['createdon'] = array(’#value’ => date(’m-d-Y’, $data->create_date));
    
            if (in_array($data->productid, $featured_products)) {
                $status[] = $data->productid;
            }
		}
	}
 
	$form['featured'] = array(
		‘#type’ => ‘checkboxes’,
		‘#options’ => $options,
		‘#default_value’ => $status,
	);
 
	$form['submit'] = array(
		‘#type’ => ’submit’,
		‘#value’ => t(’Submit’),
	);
 
	$form['cancel'] = array(
		‘#type’ => ‘markup’,
		‘#value’ => l(t(’Cancel’), ‘dashboard’),
	);
 
	$form['#redirect'] = ‘featured_product_mgmt’;
 
	return $form;
}
?>

<?php
function featured_product_form_submit($form_id, $form) {
	$form_values = $form['values'];
	$featured = $form_values['featured'];
 
	$selected_products = array();
 
	foreach($featured as $key => $value) {
		if ($value) {
			$selected_products[] = “(’$value’)”;
		}
	}
 
	$value_string = @implode(’,', $selected_products);
 
	// Delete all previous featured products
	$query = “DELETE FROM {product_featured}”;
	db_query($query);
 
	// Insert new featured products
	if (count($selected_products)) {
		$query = “INSERT INTO {product_featured}(productid) VALUES $value_string”;
		db_query($query);
	}
 
	drupal_set_message(t(’Featured product list has been updated successfully.’));
}
?>

tep 4:- Register your modules theme implementation using “hook_theme()” function.

<?php
function product_theme() {
	return array(
		‘featured_product_form’ => array(‘arguments’ => array(’form’ => NULL),),
	);
}
?>

Step 5:- Then finally define your theme function which actually format your form layout in list using the $form array. Using “foreach” loop we navigate through each item of $form array and create $rows array which we pass to “theme_table()” function later. Create the header of your table and call “table_theme()” function with $header and $rows parameters. Call the “drupal_render()” function for render the submit and cancel buttons.

<?php
function theme_featured_product_form($form) {
	$rows = array();
	foreach (element_children($form) as $key) {
		$row = array();
		if (isset($form[$key]['name'])) {
 
			$status = drupal_render($form['featured'][$key]);
			$row[] = array(’data’ => $status, ‘class’ => ‘checkbox’);
 
			$row[] = ‘‘. drupal_render($form[$key]['name']) .’‘;
			$row[] = array(’data’ => drupal_render($form[$key]['category']));
			$row[] = array(’data’ => drupal_render($form[$key]['discount']));
			$row[] = array(’data’ => drupal_render($form[$key]['createdon']));
 
			$rows[] = $row;
		}
	}
 
	// Individual table headers.
	$header = array();
	$header[] = array(’data’ => t(’Featured’), ‘class’ => ‘checkbox’);
	$header[] = t(’Name’);
	$header[] = t(’Category’);
	$header[] = t(’Discount’);
	$header[] = t(’Created on’);
 
	$output = theme(’table’, $header, $rows);
	$output .= drupal_render($form);
	return $output;
}
?>
