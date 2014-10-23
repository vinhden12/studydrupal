<?php
?>
<html>
<head>
<link rel="stylesheet" href="css/bootstrap-theme.css">
<link rel="stylesheet" href="css/bootstrap.min.css">

<link rel="stylesheet" href="css/datepicker3.css">
<link rel="stylesheet" href="css/style.css">
<script
	src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>

<script type="text/javascript" src="js/bootstrap-datepicker.js"></script>
<script type="text/javascript">
var pr;
function helloa() {
	 var w = 0;
	pr = setInterval(function (){

		$('.test .progress-bar').width(w+"%");

		 w = w+10;
		}, 100);
	setTimeout(function (){

		$('.test .progress-bar').width("100%");
	clearInterval(pr);
		R();
		}, 2000);
}

function R() {
	clearInterval(pr);
	$('.test .progress-bar').width("0%");
}

</script>
</head>

<body>


<div class="progress" style="height: 40px; margin-top: 20px;">
		<div
			class="progress-bar progress-bar-success active progress-bar-striped"
			role="progressbar" aria-valuenow="100" aria-valuemin="0"
			aria-valuemax="100" style="width: 100%; height: 100px;"></div>
	</div>
<div class="test" >
	<div class="progress" style="height: 10px; margin-top: 20px;">
		<div
			class="progress-bar progress-bar-success active progress-bar-striped"
			role="progressbar" aria-valuenow="100" aria-valuemin="0"
			aria-valuemax="100" style="width: 100%"></div>
	</div>

	<div class="progress">
		<div class="progress-bar progress-bar-striped active"
			role="progressbar" aria-valuenow="100" aria-valuemin="0"
			aria-valuemax="100" style="width: 100%">
			<span class="sr-only">45% Complete</span>
		</div>
	</div>
</div>

	<input type="button" onclick="helloa()" value="Run" />
	<input type="button" onclick="R()" value="reset" />

	<div id="sandbox-container">
		<div class="input-group date">
			<input type="text" id="date_test" class="form-control"> <span
				class="input-group-addon"><i class="glyphicon glyphicon-th"></i></span>
		</div>
	</div>
	<input type="submit" on onclick="test()" value="get dates" />

	<script type="text/javascript">
	function test() {
		var str = $('#date_test').val();
		var res = str.split(" ");

		for (x in res )
				alert(res[x]);
	}
	$('#sandbox-container .input-group.date').datepicker({
	    todayBtn: true,
	    multidate: true,
	    format: "dd/mm/yyyy",
	    multidateSeparator: " ",
	    daysOfWeekDisabled: "0,6",
	    todayHighlight: true
	});
	</script>

</body>

</html>