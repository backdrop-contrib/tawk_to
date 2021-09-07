<?php
$module_path = backdrop_get_path('module', 'tawk_to');
backdrop_add_css($module_path . '/css/tawk_to.admin.css', 'file');
?>

<div id="content" >
  <div class="l-wrapper">
    <div class="l-wrapper-inner container container-fluid">
      <div class="l-messages success-message-container" role="status" aria-label="Status messages" id="optionsSuccessMessage">
        <div class="messages status">
          <h2 class="element-invisible">Status message</h2>
          Successfully set widget options to your site
        </div>
      </div>
      <div class="l-page-title">
        <a id="main-content"></a>
      </div>
      <div class="l-content" role="main" aria-label="Main content">
        <div>
          <fieldset class="form-wrapper" id="property-widget-settings">
            <legend><span class="fieldset-legend">Property and Widget Selection</span></legend>
            <div class="fieldset-wrapper">
              <div class="fieldset-description">Select the property and widget from your tawk.to account</div>
              <?php if (!$sameUser) { ?>
                <div id="widget_already_set" class="alert alert-warning">Notice: Widget already set by other user</div>
              <?php } ?>
              <iframe id="tawkIframe" class="tawkto-property-widget-selection" src="" ></iframe>
              <input type="hidden" class="hidden" name="page_id" value="<?php echo $widget['page_id']?>">
              <input type="hidden" class="hidden" name="widget_id" value="<?php echo $widget['widget_id']?>">
            </div>
          </fieldset>
		  <?php print $visibility_opts_form ?>
        </div>
      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
  var currentHost = window.location.protocol + "//" + window.location.host;
  var url = "<?php echo $iframe_url; ?>&pltf=backdrop&parentDomain=" + currentHost;
  jQuery("#tawkIframe").attr("src", url);

  var iframe = jQuery("#tawk_widget_customization")[0];

  window.addEventListener("message", function(e) {
    if (e.origin === "<?php echo $base_url; ?>") {
      if (e.data.action === "setWidget") {
        setWidget(e);
      }

      if (e.data.action === "removeWidget") {
        removeWidget(e);
      }

      if (e.data.action === 'reloadHeight') {
        reloadIframeHeight(e.data.height);
      }
    }
  });

  function setWidget(e) {
    jQuery.post("?q=admin/config/tawk/setwidget", {
      pageId : e.data.pageId,
      widgetId : e.data.widgetId
    }, function(r) {
      if (r.success) {
        $('input[name="page_id"]').val(e.data.pageId);
        $('input[name="widget_id"]').val(e.data.widgetId);
        $('#widget_already_set').hide();
        e.source.postMessage({action: "setDone"}, "<?php echo $base_url; ?>");
      } else {
        e.source.postMessage({action: "setFail"}, "<?php echo $base_url; ?>");
      }
    });
  }

  function removeWidget(e) {
    jQuery.post("?q=admin/config/tawk/removewidget", function(r) {
      if (r.success) {
        $('input[name="page_id"]').val('');
        $('input[name="widget_id"]').val('');
        $('#widget_already_set').hide();
        e.source.postMessage({action: "removeDone"}, "<?php echo $base_url; ?>");
      } else {
        e.source.postMessage({action: "removeFail"}, "<?php echo $base_url; ?>");
      }
    });
  }

  function reloadIframeHeight(height) {
    if (!height) {
      return;
    }

    var iframe = jQuery('#tawkIframe');
    if (height === iframe.height()) {
      return;
    }

    iframe.height(height);
  }

  jQuery(document).ready(function() {
    if (jQuery("#always_display").prop("checked")) {
      jQuery('.show_specific').prop('disabled', true);
      jQuery(".div_show_specific").hide();
    } else {
      jQuery('.hide_specific').prop('disabled', true);
      jQuery(".div_hide_specific").hide();
    }

    jQuery("#always_display").change(function() {
      if (this.checked) {
        jQuery('.hide_specific').prop('disabled', false);
        jQuery('.show_specific').prop('disabled', true);
        jQuery(".div_hide_specific").show();
        jQuery(".div_show_specific").hide();
      } else {
        jQuery('.hide_specific').prop('disabled', true);
        jQuery('.show_specific').prop('disabled', false);
        jQuery(".div_hide_specific").hide();
        jQuery(".div_show_specific").show();
      }
    });
  });
</script>
