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
import dto.Mechanik;
import dto.Oprava;
import dto.OpravaS;
import java.util.Set;
import org.codehaus.plexus.util.StringUtils;
import rest.AutoClient;
import rest.MechanikClient;
import rest.OpravaClient;
import vaadin.scala.BeanItemContainer;

public class MechanikForm extends FormLayout {

    private TextField idM = new TextField("ID");
    private TextField jmenoM = new TextField("Jmeno");
    private TextField specializaceM = new TextField("Specializace");

    private Button save = new Button("Save");
    private Button delete = new Button("Delete");
    private Button update = new Button("Update");

    private MechanikClient mechanikClient = new MechanikClient();
    private OpravaClient opravaClient = new OpravaClient();

    private Mechanik mechanik;
    private MyUI myUI;

    public MechanikForm(MyUI myUI) {
        this.myUI = myUI;

        setSizeUndefined();
        HorizontalLayout buttons = new HorizontalLayout(save, delete, update);
        addComponents(idM, jmenoM, specializaceM, buttons);

        save.setStyleName(ValoTheme.BUTTON_PRIMARY);
        save.setClickShortcut(KeyCode.ENTER);

        save.addClickListener(e -> this.save());
        delete.addClickListener(e -> this.delete());
        update.addClickListener(e -> this.update());
    }

    public boolean checkMechanikFields() {
        String idMField = idM.getValue();
        boolean checkIdMField = StringUtils.isNumeric(idMField);
        String jmenoMField = jmenoM.getValue();
        String specializaceMField = specializaceM.getValue();

        if (checkIdMField && !idMField.equals("") && !jmenoMField.equals("") && !specializaceMField.equals("")) {
            return true;
        } else {
            return false;
        }
    }

    public boolean checkIfOpravaExists(int idM) {

        OpravaS opravaS = opravaClient.findAllOpravaS_JSON(OpravaS.class);
        for (Oprava oprava : opravaS.getOpravaS()) {
            if (oprava.getIdM().getIdM() == idM) {
                return true;
            }
        }

        return false;
    }

    public Mechanik setMechanik() {

        if (checkMechanikFields()) {
            Mechanik entity = new Mechanik();
            entity.setIdM(Integer.parseInt(idM.getValue()));
            entity.setJmenoM(jmenoM.getValue());
            entity.setSpecializaceM(specializaceM.getValue());
            return entity;
        } else {
            return null;
        }
    }

    private void delete() {
        String idMField = idM.getValue();
        boolean checkIdMField = StringUtils.isNumeric(idMField);

        if (checkIdMField && !idMField.equals("")) {
            Mechanik mechanikTmp = mechanikClient.find_JSON(Mechanik.class, idMField);
            if (mechanikTmp != null) {
                if (checkIfOpravaExists(mechanikTmp.getIdM())) {
                    Notification.show("CAN'T DELETE", "This [MECHANIK] has [OPRAVA]", Notification.Type.HUMANIZED_MESSAGE);
                } else {
                    mechanikClient.remove(idMField);
                    myUI.updateMechanikList();
                }
            } else {
                Notification.show("DOESN'T EXISTS", "This [MECHANIK] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }

    }

    private void save() {
        if (checkMechanikFields()) {
            String idMField = idM.getValue();

            if (mechanikClient.find_JSON(Mechanik.class,
                    idMField) == null) {
                Mechanik entity = setMechanik();
                mechanikClient.create_JSON(entity);
                myUI.updateMechanikList();
            } else {
                Notification.show("ALREADY EXISTS", "This [MECHANIK] is already in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

    private void update() {
        if (checkMechanikFields()) {
            String idAField = idM.getValue();

            if (mechanikClient.find_JSON(Auto.class,
                    idAField) != null) {
                Mechanik entity = setMechanik();
                mechanikClient.edit_JSON(entity, Integer.toString(entity.getIdM()));
                myUI.updateMechanikList();
            } else {
                Notification.show("DOESN'T EXISTS", "This [MECHANIK] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

}
