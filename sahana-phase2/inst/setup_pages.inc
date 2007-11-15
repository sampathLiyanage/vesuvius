<?php
/**Page generation functions of the Sahana Advanced Web Setup
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue. <ravithb@yahoo.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage setup
*/
/**
 * Setup general dependencies such as GD and Gettext.
 *
 */
function shn_setup_general_dependancies()
{
	global $global;
	$isOK = true;
	$tick_img = '<img align="top" src="theme/default/img/tic.png" alt="tick"/>';
	$cross_img = '<img align="top" src="theme/default/img/cross.png" alt="cross"/>';
	$oops_img = '<img align="bottom" src="theme/default/img/oops.png" alt="oops"/>';
	// this is the first step in all setups.
	$step_no = 1;
	$_SESSION['setup_step_no'] = 1;

	?>
<h1><?=_('Sahana Web Setup - Step ').$step_no?></h1>

<p><?=_('Welcome to Sahana. Please follow the following steps to setup the Sahana system')?></p>

<p><?=_('First we need to check if all the relevant dependencies for the Sahana system to be install are available on your system')?></p>
	<?php

	shn_form_fopen('CHECK_DEPENDENCIES','setup');

	shn_form_fsopen(_('PHP libraries'));
	?>
<p><?=_('The following checks if all the relevant Sahana libraries are installed')?></p>
	<?php

	$value = (version_compare(phpversion(), '4.1', '>'));
	$isOK &= $value;

	//if ($isOK) echo "is OK";
	if ($value) {
		shn_form_label(_('PHP Version'), $tick_img.phpversion()." is installed");
	} else {
		shn_form_label(_('PHP Version'), $cross_img.phpversion()." is installed");
		echo "<p><br/>$oops_img Sahana needs PHP version 4.1 or higher. Please upgrate your version of PHP</p>";
	}

	// Check if php-gd is loaded
	$value = (extension_loaded('gd'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_('PHP-GD Library'), $tick_img."installed");
	} else {
		shn_form_label(_('PHP-GD Library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-GD for image manipulations. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	// Check if php-gettext is loaded
	$value = (extension_loaded('gettext'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_('PHP-gettext Library'), $tick_img."installed");
	} else {
		shn_form_label(_('PHP-gettext Library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-gettext for to support local languages. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	$value = (extension_loaded('mysql'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_('MySQL library'), $tick_img."installed");
	} else {
		shn_form_label(_('MySQL library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-MySQL library and MySQL for database operation. Please install PHP-MySQL library and MySQL and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	shn_form_fsclose();
	shn_form_fsopen(_('File and Directory Permissions'));
	?>
<p><?=_('The following checks if certain files and sub-directories have write permissions for Sahana to function,')?></p>
	<?php
	$tmpWritable = is_writable($global['approot'].'www/tmp');
	$isOK &= $tmpWritable;


	if ($tmpWritable) {
		//shn_form_label(_('Sahana www/tmp/ is writable?'),"The Sahana sub-directory writable");
		shn_form_label(_('<i>sahana/www/tmp/</i>'),"is <strong><font color=green>writable</font></strong>!<br>");
	} else {
		//shn_form_label(_('Sahana www/tmp/ is writable?'),"The Sahana sub-directory not writable");
		shn_form_label(_('<i>sahana/www/tmp/</i>'),"is <strong><font color=red>not writable</font></strong>!<br>");
		//echo "<p><br/>$oops_img The directory ".$global['approot']."www/tmp needs to be writable by the web server at least. Please change the permissions of this directory and try again.</p>";
	}

	/* if ($value) {
	 shn_form_label(_('Sahana www/tmp/ is writable?'), $tick_img."The Sahana sub-directory writable");
	 } else {
	 shn_form_label(_('Sahana www/tmp/ is writable?'), $cross_img."The Sahana sub-directory not writable");
	 echo "<p><br/>$oops_img The directory ".$global['approot']."www/tmp needs to be writable by the web server at least. Please change the permissions of this directory and try again.</p>";
	 }

	 /*   $value = (is_writable($global['approot'].'res/locale'))? 'checked':'';

	 shn_form_checkbox('Sahana res/locale is writable?','write_locale',$value.'
	 disabled="true"',array('value'=>'y','help'=>'hello'));
	 */
	$confWritable = is_writable($global['approot'].'conf');

	if ($confWritable) {
		//shn_form_label(_('Sahana www/conf/ is writable?'), $tick_img."The Sahana sub-directory writable");
		shn_form_label(_('<i>sahana/conf/</i>'),"is <strong><font color=green>writable</font></strong>!<br>");
	} else {
		//shn_form_label(_('Sahana www/conf/ is writable?'), "The Sahana sub-directory not writable");
		shn_form_label(_('<i>sahana/conf/</i>'),"is <strong><font color=red>not writable</font></strong>!<br>");
	}

	if (!$tmpWritable || !$confWritable) {
		$both = (!$tmpWritable && !$confWritable);

		echo "<p>Note: <font color=gray>" . (($both ? "both " : "")) . ((!$confWritable) ? "<strong>sahana/conf/</strong>" : "") . (($both) ? " and " : " ") . ((!$tmpWritable) ? "<strong>sahana/www/tmp/</strong>" : "") . " need" . ((!$both) ? "s" : "") . " to be writable by the web server at least. Please change the permissions of " . ((!$both) ? "this directory" : "these directories") . " and try again.</font></p>";
	}

	shn_form_fsclose();

	if ($isOK) {
		echo _('<p>All the dependencies are OK and you may move to
                the next step</p>')."\n";
		shn_form_submit(_('Next >>'));
	} else {
		echo _('<p>Please correct the required dependencies above and</p>')."\n";
		shn_form_submit(_('Try Again'));
	}
	shn_form_fclose();
}

/**
 * Generate the select setup page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_select_setup($step_no=null)
{
	global $global;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php echo _('Sahana Database Setup - Step ').$step_no?></h2>
	<?php
	shn_form_fopen('SELECT_SETUP');
	shn_form_fsopen(_('Select a setup type to continue.'));
	shn_form_fsopen(_("Simple Setup"));
	echo _("To setup the most common modules and configuration.");
	echo "<br/>";
	shn_form_submit(_("Simple"),'name="setup_type_simple"');
	shn_form_fsclose();
	shn_form_fsopen(_("Advanced Setup"));
	echo _("To customize modules and configuration.");
	echo "<br/>";
	shn_form_submit(_("Advanced"),'name="setup_type_adv"');
	shn_form_fsclose();
	//shn_form_submit(_("Scenario Based"),'name="setup_type_scen"');
	shn_form_fsclose();
	shn_form_fclose();
}

/**
 * Generate the database setup page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_simple_dbsetup($step_no=null)
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php
echo _('Sahana Web Setup - Step ').$step_no;
?></h2>
<?php
display_errors();
shn_form_fopen('DATABASE_SETUP');
if(isset($_SESSION['setup_system_db_user_exists'])){
	/*
	 * 	Duplicate system database username. Confirm to keep or give a different name.
	 */

	shn_form_fsopen('User Exists.');
	echo "<div class='warning message'>";
	echo _("Database user name sahana_sys already exists.                                                         
To continue, select a different user name. If you want to keep the existing user click on 'Keep User'. ");
	echo "</div>";
	//add_warning('test');
	shn_form_submit(_('Keep User'),'name="keep_ex_user"');
	shn_form_fsclose();
}

if(isset($_SESSION['setup_system_db_exists'])){
	/*
	 * 	Duplicate system database. Confirm to keep or give a different name.
	 */
	shn_form_fsopen('Database Exists.');
	echo "<div class='warning message'>";
	echo _("Database sahana already exists.
Enter a different database name to continue. Press 'Drop Database' to delete the database and to continue installation.");
	echo "</div>";
	shn_form_submit(_('Drop Database'),'name="drop_ex_db"');
	shn_form_fsclose();
}
shn_form_fsopen(_('Database'));
shn_form_select(
array( 'mysql' => 'MySQL 4.1 or above','pgsql"disabled="disabled' => 'PostgreSQL'),
                'Database Types', 'db_type');
shn_form_text(_('Database Host:Port'),'db_host','size="30"',
array('value'=>'localhost:3306','req'=>true ));
shn_form_text(_('Database Name'),'db_name','size="30"',
array('value'=>'sahana','req'=>true));
shn_form_text(_('Database User'),'root_db_user','size="30"',
array('value'=>'','req'=>true));
shn_form_password(_('Database Password'),'root_db_pass','size="30"', array('value'=>'','req'=>true));
shn_form_text(_('System Database User'),'db_user','size="30"',array('value'=>'sahana_sys','req'=>true));
shn_form_password(_('System Database Password'),'db_pass','size="30"',array('value'=>'password','req'=>true));

//show only in simple setup
if(_shn_setup_get_setup_type() == SIMPLE_SETUP){
	// add sample data check box.
	shn_form_checkbox(_('Create Sample Data.'),'dbsample','checked',
	array('value'=>'y'));
}

shn_form_fsclose();
shn_form_submit(_('<< Back'),'name="back_button"');
shn_form_submit(_('Setup Database >>'));


shn_form_fclose();
}

/**
 * Generate teh simple configuration page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_simple_config($step_no=null)
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php
echo _("Sahaha Web Setup - Step ").$step_no;
?></h2>
<p><?php echo _("Please follow the following steps to setup the Sahana configuration.") ?></p>

<?php
display_errors();
global $global ,  $conf;
?>
<script
	type="text/javascript" src="res/js/styleswitcher.js"></script>
<noscript>Style change preview is not available, without javascript
support.</noscript>

<?php
shn_form_fopen('SIMPLE_CONFIGURATION');

// pass the previous post varibles into hidden for the configuration file

shn_form_fsopen(_('Installation Details'));

echo '<p>The following details are needed to uniquely identify your Sahana installation</p>'; // some spellings corrected by chamath 2007-03-15 09:50

$help_txt = "The following field is randomly generated to help uniquely identify \
                 this Sahana installation. Please use this unless you have a \
                 convention defined";
shn_form_text(_('Unique Installation ID'),'base_uuid','size="4" maxlength="4"',
array('value'=> shn_generate_uuid(4),'req'=>true , 'help' => $help_txt));
shn_form_text(_('Administrator Name'),'root_name','size="40"',array('req'=>true ));
shn_form_text(_('Administrator Email'),'root_email','size="40"' );
shn_form_text(_('Administrator Telephone'),'root_tel','size="30"' );

shn_form_fsclose();

shn_form_fsopen(_('Administrator Account'));
shn_form_text(_('Admin User Name'),'admin_name','size="40"', array('req'=>true, 'value'=>'admin','help'=>'The root user is the administrator
                of the system and has the greatest privilages') );
shn_form_password(_('Password'),'root_pwd','size="30"',
array('req'=>true));
shn_form_password(_('Confirm Password'),'root_pwd_confirm','size="30"',array('req'=>true));
shn_form_fsclose();

shn_form_fsopen(_('Create Normal User Account'));
shn_form_text(_('Normal User Name'),'user_name','size="40"', array('req'=>true,'value'=>'sahana', 'help'=>'Please login as this user for non-admin work') );
shn_form_password(_('Password'),'user_pwd','size="30"',array('req'=>true));
shn_form_password(_('Confirm Password'),'user_pwd_confirm','size="30"',array('req'=>true));
shn_form_fsclose();

shn_form_fsopen(_('Configuration File'));

if (is_writeable($global['approot'].'conf')) {

	echo '<p>The next step is to write the configuration file sysconf.inc in the Sahana /conf directory.</p>';

} else {

	echo '<p>The PHP/Web Server should normally not have access to write
    or modify the configuration file located in Sahana application <b>/conf</b> 
    directory, as this is a security risk. Please specify where to write the temporary file (e.g. /tmp). Subsequently you need to move this file to 
    the Sahana <b>/conf</b> directory.</p>';

	$tmp_filename = tempnam('/tmp','sysconf.inc');
	// Need the temporary directory rather than the filename
	$tmp_filename = preg_replace('/sysconf.inc.*$/','sysconf.inc',
	$tmp_filename);

	shn_form_text(_('Location To Write Config File (sysconf.inc)'),
                'conffile','size="50"', array('value'=>"$tmp_filename",
                'req'=>true ));

}
shn_form_fsclose();
shn_form_submit(_('<< Back'),'name="back_button"');
shn_form_submit(_('Write Configuration File >>'));

shn_form_fclose();
}

/**
 * Generate the module selection page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_select_modules($step_no=null){
	global $global, $conf;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php 
echo _("Sahaha Web Setup - Step ").$step_no;
?></h2>
<p><?php echo _("Please follow the following steps to setup the Sahana configuration.") ?></p>

<?php
display_errors();


// load configuration
shn_config_module_conf_fetch('all');

$all_modules = shn_get_all_modules();
asort($all_modules);

$_essencial_modules = array ('home','admin','gis');

shn_form_fopen('ADV_SELECT_MODULES');
shn_form_fsopen(_("Sahana Core"));
echo _("The following core modules will be installed by default.");
echo "<hr/><ul>";
foreach($_essencial_modules as $esmod){
	echo "<li>".shn_get_module_name($esmod)."</li>";
}
echo "</ul>";
shn_form_fsclose();

shn_form_fsopen(_('Please select the required modules'));
foreach($all_modules as $key=>$value){
	if(in_array($value[0],$_essencial_modules)){
		// put the value in session directly.
		_shn_setup_put_value_in_session($value[0],true);
	}else{
		shn_form_checkbox($value[1],'module_'.$value[0],'onchange=selectDepModsInUI(this)',array('value'=>$value[0]));
	}
}

//include_once($global['approot']."/tools/jdebug.php");
?>
<script type="text/javascript">

var allDeps = new Array();
// number of hits per module
var arrHits = new Array();
<?php
	// remove essencial modules
	// so that no javascript is generated for them
	$new_arr = array();
	foreach($all_modules as $key=>$value){
		if(in_array($value[0],$_essencial_modules)==false){
			$new_arr[$key]=$value;
		}
	}
	$all_modules = $new_arr;

	foreach($all_modules as $key=>$value){
		if(isset($conf['mod_'.$value[0].'_dependencies'])){

			echo "allDeps['".$value[0]."'] = new Array(";
			
			// get the dependant modules by splitting the dependencies string.
			$dep_mods = explode(",",'"'.$conf['mod_'.$value[0].'_dependencies'].'"');
			// generate a string of all dependant modules separated by commas.
			$mods_str = "";
			$_j = 0;
			foreach($dep_mods as $mod_code){
				if($_j>0){
					$mods_str .= "\",\"".$mod_code;
				}else{
					// first time no preceding comma.
					$mods_str = $mod_code;
				}
				$_j++;
			}
			echo $mods_str.");\n";
		}
		echo "arrHits['".$value[0]."'] = 0;\n";
	}
		?>
	
	function selectDepModsInUI(src){
		var checkBoxes = document.getElementsByTagName('input');
		var mod_deps = allDeps[src.value];

		if(mod_deps != null){

			// for each module in the module dependency list
			for(j=0;j<mod_deps.length;j++){
				
				if(src.checked==true){
					// increment hits
					arrHits[mod_deps[j]]++;
				}else{
					// 	decrement hits
					arrHits[mod_deps[j]]--;
				}
				
				// check the dependent check boxes algorithm
				for(k=0;k<checkBoxes.length;k++){
					// get only the check boxes.
					if(checkBoxes[k].getAttribute("type")=="checkbox" && (checkBoxes[k].id.indexOf("module_")>-1)){
						if(checkBoxes[k].value == mod_deps[j]){
							if(arrHits[checkBoxes[k].value]!=null && arrHits[checkBoxes[k].value]>0){
								// there are other modules that depend which are selected
								// keep selected and disabled.
								checkBoxes[k].checked = true;
								checkBoxes[k].disabled = true;
							}else{
								// no modules dependant are selected.
								checkBoxes[k].checked = src.checked;
								checkBoxes[k].disabled = src.checked;
							}					
						}
					}
				}										
			}
			
			
		} 
	}
//-->
</script>
		<?php
		shn_form_fsclose();
		shn_form_submit(_('<< Back'),'name="back_button"');
		shn_form_submit(_('Next >>'));
		shn_form_fclose();
}

/**
 * Generate the advanced configuration page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_advanced_config($step_no=null){
	global $global, $conf;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php 
echo _("Sahaha Web Setup - Step ").$step_no;
?></h2>

<?php
display_errors();
shn_form_fopen('ADV_CONFIG_MODULES');
shn_form_fsopen(_('System Settings'));

shn_form_select(
array( 'disable' => _('Disable'),'enable' =>_('Enable')),
_('Access Control'),'acl');

// create the associative array of themes.
$available_themes = _shn_setup_get_available_themes();
$themelist = array();
foreach($available_themes as $tname){
	if($tname!=$conf['theme']){
		?>
<link rel="stylesheet"
	media="screen, projection" type="text/css"
	href="theme/<?=$tname?>/sahana.css" />
<link rel="stylesheet"
	media="print" type="text/css" href="theme/<?=$tname?>/print.css" />
<link rel="stylesheet"
	media="handheld" type="text/css" href="theme/<?=$tname?>/mobile.css" />
		<?php
}
$themelist[$tname] = ucwords($tname)._(' Theme');
}
shn_form_select($themelist,_('Theme'),'theme','onchange=setActiveStyleSheet(this.options[this.selectedIndex].value)');
shn_form_fsclose();
shn_form_submit(_('<< Back'),'name="back_button"');
shn_form_submit(_("Next >>"));

$selected_modules = _shn_setup_get_selected_modules();
if(isset($selected_modules)){
	// load configuration
	shn_config_module_conf_fetch('all');

	foreach($selected_modules as $sel_mod){
		// include the module specific setup.inc
		$mod_setup_file = $global['approot']."mod/".$sel_mod."/ins/setup.inc";
		if(file_exists($mod_setup_file)){
			include_once($mod_setup_file);
			// the module specific configuration page generator callback function.
			$mod_conf_page_func = "_shn_".$sel_mod."_setup_config_page";
			if(function_exists($mod_conf_page_func)){
				shn_form_fsopen(shn_get_module_name($sel_mod)._(" Configuration"));
				$mod_conf_page_func();
				shn_form_fsclose();
				shn_form_submit(_('<< Back'),'name="back_button"');
				shn_form_submit(_("Next >>"));
			}
		}
	}
}

shn_form_fclose();
}

/**
 * Generate the password policy configuratio page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_pwd_policy($step_no=null){
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h1><?php 
echo _("Sahaha Web Setup - Step ").$step_no;
?></h1>
<?php
display_errors();
shn_form_fopen('ADV_PWD_POLICY');
shn_form_fsopen(_('Define a system wide password policy'));
shn_form_text(_('Minimum No of characters'),'pwd_min_chars','maxlength="2" size="2"',array('value'=>8));
shn_form_text(_('Maximum No of characters'),'pwd_max_chars','maxlength="2" size="2"',array('value'=>16,'maxlength'=>2,'size'=>2));
shn_form_checkbox(_('should contain uppercase characters'),'has_uppercase');
echo "<br/>";
shn_form_checkbox(_('should contain numbers'),'pwd_has_numbers');
echo "<br/>";
shn_form_checkbox(_('should contain special characters'),'pwd_has_spchars');
echo "<br/>";
shn_form_checkbox(_('should not contain the username'),'pwd_has_username');
echo "<br/>";
shn_form_checkbox(_('should not contain repeating patterns'),'pwd_has_reppatterns');
shn_form_fsclose();
shn_form_submit(_('<< Back'),'name="back_button"');
shn_form_submit(_("Next >>"));
shn_form_fclose();
}


/**
 * Generate the complete setup page.
 *
 */
function shn_setup_complete(){
	global $global;
	$oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';
	?>
<h1><?php 
echo _("Sahaha Web Setup - Step ").$step_no;
?></h1>
<?php
display_errors();
shn_form_fopen('default','admin',array('req_message' => false));
shn_form_fsopen(_('Starting Sahana'));

$sahana_url = 'http://'.$_SERVER['HTTP_HOST'].preg_replace('/index.php\?.*$/','',$_SERVER['REQUEST_URI']);
shn_form_hidden(array('shn_url'=>$sahana_url));

if (is_writeable($global['approot'].'conf')) {
	?>
<p><b><u><?php echo $oops_img._('WARNING: Security')?></u></b></p>
<p><?php echo _('To secure the configuration you have to remove write 
             permissions from the configuration file sysconf.inc located in 
             the Sahana directory conf/');?></p>

<p><?php echo _('Click the button below to start Sahana');?> <?php
}
shn_form_fsclose();
shn_form_submit(_('Start Sahana'));
session_destroy();
shn_form_fclose();
}

/**
 * Show any errors occurred during setup and an option to restart the setup.
 *
 */
function shn_setup_error(){
	global $global;

	?>
<h1><?php
echo _("Setup Error");
?></h1>
<?php
display_errors();
shn_form_fopen('default','admin',array('req_message' => false));
shn_form_fsopen(_('Restart Setup'));
?>
<p><?php echo _('Click the button below to restart the setup.');?></p>
<?php
shn_form_fsclose();
shn_form_submit(_('Restart Setup'));
session_destroy();
shn_form_fclose();
}

/**
 * Generate the Sahana Header
 *
 */
function shn_setup_header()
{
	?>
<body>
<div id="container"><?php 
shn_include_page_section('header',$module);
?>
<div id="wrapper" class="clearfix">
<div id="content" class="clearfix"><?php
}

/**
 * Generate the Sahana Footer
 *
 */
function shn_setup_footer()
{
	?></div>
<!-- /content --> <?php
shn_include_page_section('footer',$module);
?></div>
<!-- /wrapper --></div>
<!-- /container -->
</body>
</html>
<?php
}
?>