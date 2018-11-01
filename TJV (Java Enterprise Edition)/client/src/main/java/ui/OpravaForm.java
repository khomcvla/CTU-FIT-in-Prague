package ui;

import com.oracle.jrockit.jfr.InvalidValueException;
import com.vaadin.data.Binder;
import com.vaadin.data.Validator;
import com.vaadin.event.ShortcutAction.KeyCode;
import com.vaadin.ui.Button;
import com.vaadin.ui.DateField;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.HorizontalLayout;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Notification;
import com.vaadin.ui.TextField;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.themes.ValoTheme;
import dto.Auto;
import dto.Mechanik;
import dto.Oprava;
import java.util.ArrayList;
import java.util.List;
import org.codehaus.plexus.util.StringUtils;
import rest.AutoClient;
import rest.MechanikClient;
import rest.OpravaClient;

public class OpravaForm extends FormLayout {

    private TextField idO = new TextField("ID");
    private TextField cenaO = new TextField("Cena");
    private TextField diagnostikaO = new TextField("Diagnostika");
    private TextField idA = new TextField("idA");
    private TextField idM = new TextField("idM");

    private Button save = new Button("Save");
    private Button delete = new Button("Delete");
    private Button update = new Button("Update");

    private AutoClient autoClient = new AutoClient();
    private MechanikClient mechanikClient = new MechanikClient();
    private OpravaClient opravaClient = new OpravaClient();

    private Oprava oprava;
    private MyUI myUI;

    public OpravaForm(MyUI myUI) {
        this.myUI = myUI;

        setSizeUndefined();
        HorizontalLayout buttons = new HorizontalLayout(save, delete, update);
        addComponents(idO, idA, idM, cenaO, diagnostikaO, buttons);

        save.setStyleName(ValoTheme.BUTTON_PRIMARY);
        save.setClickShortcut(KeyCode.ENTER);

        save.addClickListener(e -> this.save());
        delete.addClickListener(e -> this.delete());
        update.addClickListener(e -> this.update());

    }

    public boolean checkOpravaFields() {
        String idOField = idO.getValue();
        String idAField = idA.getValue();
        String idMField = idM.getValue();
        boolean checkIdOField = StringUtils.isNumeric(idOField);
        boolean checkIdAField = StringUtils.isNumeric(idAField);
        boolean checkIdMField = StringUtils.isNumeric(idMField);

        String cenaOField = cenaO.getValue();
        boolean checkCenaOField = StringUtils.isNumeric(cenaOField);

        String diagnostikaOField = diagnostikaO.getValue();

        if (checkIdOField && checkIdAField && checkIdMField && checkCenaOField && !cenaOField.equals("") && !diagnostikaOField.equals("")) {
            return true;
        } else {
            return false;
        }
    }

    public Oprava setOprava() {
        if (checkOpravaFields()) {
            Oprava entity = new Oprava();
            entity.setIdO(Integer.parseInt(idO.getValue()));
            entity.setCenaO(Integer.parseInt(cenaO.getValue()));
            entity.setDiagnostikaO(diagnostikaO.getValue());

            //TODO check if exists
            Auto auto = autoClient.find_JSON(Auto.class, idA.getValue());
            if (auto == null) {
                return null;
            }

            Mechanik mechanik = mechanikClient.find_JSON(Mechanik.class, idM.getValue());
            if (mechanik == null) {
                return null;
            }

            entity.setIdA(auto);
            entity.setIdM(mechanik);

            // List for autoOprava
            List<Oprava> autoOpravaList = auto.getOpravaList();
            if (autoOpravaList == null) {
                autoOpravaList = new ArrayList();
                autoOpravaList.add(entity);
                auto.setOpravaList(autoOpravaList);
            } else {
                autoOpravaList.add(entity);
                auto.setOpravaList(autoOpravaList);
            }

            //List for mechanikOprava
            List<Oprava> mechanikOpravaList = mechanik.getOpravaList();
            if (mechanikOpravaList == null) {
                mechanikOpravaList = new ArrayList();
                mechanikOpravaList.add(entity);
                mechanik.setOpravaList(mechanikOpravaList);
            } else {
                mechanikOpravaList.add(entity);
                mechanik.setOpravaList(mechanikOpravaList);
            }

            return entity;
        } else {
            return null;
        }

    }

    private void delete() {
        String idOField = idO.getValue();
        boolean checkIdOField = StringUtils.isNumeric(idOField);

        if (checkIdOField && !idOField.equals("")) {
            if (opravaClient.find_JSON(Oprava.class, idOField) != null) {
                opravaClient.remove(idOField);
                myUI.updateOpravaList();
            } else {
                Notification.show("DOESN'T EXISTS", "This auto isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }
        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }

    }

    private void save() {
        if (checkOpravaFields()) {
            String idOField = idO.getValue();
            String idAField = idA.getValue();
            String idMField = idM.getValue();

            Oprava opravaTmp = opravaClient.find_JSON(Oprava.class, idOField);
            Auto autoTmp = autoClient.find_JSON(Auto.class, idAField);
            Mechanik mechanikTmp = mechanikClient.find_JSON(Mechanik.class, idMField);

            if (opravaTmp == null) {
                if (autoTmp != null) {
                    if (mechanikTmp != null) {
                        Oprava entity = setOprava();
                        opravaClient.edit_JSON(entity, Integer.toString(entity.getIdO()));
                        myUI.updateOpravaList();
                    } else {
                        Notification.show("DOESN'T EXISTS", "This [MECHANIK] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
                    }
                } else {
                    Notification.show("DOESN'T EXISTS", "This [AUTO] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
                }
            } else {
                Notification.show("ALREADY EXISTS", "This [OPRAVA] is already in database", Notification.Type.HUMANIZED_MESSAGE);
            }

        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

    private void update() {
        if (checkOpravaFields()) {
            String idOField = idO.getValue();
            String idAField = idA.getValue();
            String idMField = idM.getValue();

            Oprava opravaTmp = opravaClient.find_JSON(Oprava.class, idOField);
            Auto autoTmp = autoClient.find_JSON(Auto.class, idAField);
            Mechanik mechanikTmp = mechanikClient.find_JSON(Mechanik.class, idMField);

            if (opravaTmp != null) {
                if (autoTmp != null) {
                    if (mechanikTmp != null) {
                        Oprava entity = setOprava();
                        opravaClient.edit_JSON(entity, Integer.toString(entity.getIdO()));
                        myUI.updateOpravaList();
                    } else {
                        Notification.show("DOESN'T EXISTS", "This [MECHANIK] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
                    }
                } else {
                    Notification.show("DOESN'T EXISTS", "This [AUTO] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
                }
            } else {
                Notification.show("DOESN'T EXISTS", "This [OPRAVA] isn't in database", Notification.Type.HUMANIZED_MESSAGE);
            }

        } else {
            Notification.show("INCORRECT INPUT", "Check your input fields!", Notification.Type.HUMANIZED_MESSAGE);
        }
    }

}
