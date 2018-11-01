package ui;

import com.vaadin.data.Binder;
import com.vaadin.data.Validator;
import com.vaadin.event.ShortcutAction.KeyCode;
import com.vaadin.ui.Button;
import com.vaadin.ui.DateField;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Grid.SelectionMode;
import com.vaadin.ui.HorizontalLayout;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Notification;
import com.vaadin.ui.TextField;
import com.vaadin.ui.components.grid.SingleSelectionModel;
import com.vaadin.ui.themes.ValoTheme;
import dto.Auto;
import dto.Oprava;
import dto.OpravaS;
import java.util.Set;
import org.codehaus.plexus.util.StringUtils;
import rest.AutoClient;
import rest.OpravaClient;
import vaadin.scala.BeanItemContainer;

public class AutoForm extends FormLayout {

    private TextField idA = new TextField("ID");
    private TextField znackaA = new TextField("Znacka");
    private TextField modelA = new TextField("Model");

    private Button save = new Button("Save");
    private Button delete = new Button("Delete");
    private Button update = new Button("Update");

    private AutoClient autoClient = new AutoClient();
    private OpravaClient opravaClient = new OpravaClient();

    private Auto auto;
    private MyUI myUI;

    public AutoForm(MyUI myUI) {
        this.myUI = myUI;

        setSizeUndefined();
        HorizontalLayout buttons = new HorizontalLayout(save, delete, update);
        addComponents(idA, znackaA, modelA, buttons);

        save.setStyleName(ValoTheme.BUTTON_PRIMARY);
        save.setClickShortcut(KeyCode.ENTER);

        save.addClickListener(e -> this.save());
        delete.addClickListener(e -> this.delete());
        update.addClickListener(e -> this.update());
    }

    public boolean checkAutoFields() {
        String idAField = idA.getValue();
        boolean checkIdAField = StringUtils.isNumeric(idAField);
        String znackaAField = znackaA.getValue();
        String modelAField = modelA.getValue();

        if (checkIdAField && !idAField.equals("") && !znackaAField.equals("") && !modelAField.equals("")) {
            return true;
        } else {
            return false;
        }
    }

    public boolean checkIfOpravaExists(int idA) {

        OpravaS opravaS = opravaClient.findAllOpravaS_JSON(OpravaS.class);
        for (Oprava oprava : opravaS.getOpravaS()) {
            if (oprava.getIdA().getIdA() == idA) {
                return true;
            }
        }

        return false;
    }

    public Auto setAuto() {

        if (checkAutoFields()) {
            Auto entity = new Auto();
            entity.setIdA(Integer.parseInt(idA.getValue()));
            entity.setZnackaA(znackaA.getValue());
            entity.setModelA(modelA.getValue());
            return entity;
        } else {
            return null;
        }
    }

    private void delete() {
        String idAField = idA.getValue();
        boolean checkIdAField = StringUtils.isNumeric(idAField);

        if (checkIdAField && !idAField.equals("")) {
            Auto autoTmp = autoClient.find_JSON(Auto.class, idAField);
            if (autoTmp != null) {
                if (checkIfOpravaExists(autoTmp.getIdA())) {
                    Notification.show("CAN'T DELETE", "This [AUTO] has [OPRAVA]", Notification.Type.HUMANIZED_MESSAGE);
                } else {
                    autoClient.remove(idAField);
                    myUI.updateAutoList();
                }
            } else {
                Notification.show("DOESN'T EXISTS", "This [AUTO] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }

    }

    private void save() {
        if (checkAutoFields()) {
            String idAField = idA.getValue();
            Auto autoTmp = autoClient.find_JSON(Auto.class, idAField);
            if (autoTmp == null) {
                Auto entity = setAuto();
                autoClient.create_JSON(entity);
                myUI.updateAutoList();
            } else {
                Notification.show("ALREADY EXISTS", "This [AUTO] is already in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

    private void update() {
        if (checkAutoFields()) {
            String idAField = idA.getValue();
            Auto autoTmp = autoClient.find_JSON(Auto.class, idAField);
            if (autoTmp != null) {
                Auto entity = setAuto();
                autoClient.edit_JSON(entity, Integer.toString(entity.getIdA()));
                myUI.updateAutoList();
            } else {
                Notification.show("DOESN'T EXISTS", "This [AUTO] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

}
