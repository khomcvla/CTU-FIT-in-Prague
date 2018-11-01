package ui;

import javax.servlet.annotation.WebServlet;

import com.vaadin.annotations.Theme;
import com.vaadin.annotations.VaadinServletConfiguration;
import com.vaadin.icons.VaadinIcons;
import com.vaadin.server.Sizeable;
import com.vaadin.server.VaadinRequest;
import com.vaadin.server.VaadinServlet;
import com.vaadin.shared.ui.ValueChangeMode;
import com.vaadin.ui.Button;
import com.vaadin.ui.CssLayout;
import com.vaadin.ui.Grid;
import com.vaadin.ui.HorizontalLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.components.grid.HeaderRow;
import com.vaadin.ui.components.grid.SingleSelectionModel;
import com.vaadin.ui.themes.ValoTheme;
import dto.Auto;
import dto.AutoS;
import dto.Mechanik;
import dto.MechanikS;
import dto.Oprava;
import dto.OpravaS;
import java.util.List;
import rest.AutoClient;
import rest.MechanikClient;
import rest.OpravaClient;

/**
 * This UI is the application entry point. A UI may either represent a browser
 * window (or tab) or some part of an HTML page where a Vaadin application is
 * embedded.
 * <p>
 * The UI is initialized using {@link #init(VaadinRequest)}. This method is
 * intended to be overridden to add component to the user interface and
 * initialize non-component functionality.
 */
@Theme("mytheme")
public class MyUI extends UI {

    private AutoClient autoClient = new AutoClient();
    public Grid<Auto> autoGrid = new Grid<>(Auto.class);
    private AutoForm autoForm = new AutoForm(this);

    private MechanikClient mechanikClient = new MechanikClient();
    public Grid<Mechanik> mechanikGrid = new Grid<>(Mechanik.class);
    private MechanikForm mechanikForm = new MechanikForm(this);

    private OpravaClient opravaClient = new OpravaClient();
    public Grid<Oprava> opravaGrid = new Grid<>(Oprava.class);
    private OpravaForm opravaForm = new OpravaForm(this);

    private HorizontalLayout layout = new HorizontalLayout();

    @Override
    protected void init(VaadinRequest vaadinRequest) {
        layout.setSpacing(true);
        layout.addStyleName("layout-with-border");

        showAutoForm();
        showMechanikForm();
        showOpravaForm();

        setContent(layout);
    }

    public void showAutoForm() {
        
        autoGrid.setColumns("idA", "znackaA", "modelA");
        VerticalLayout autoMain = new VerticalLayout(autoGrid, autoForm);
        autoMain.setSizeFull();
        HeaderRow autoHead = autoGrid.prependHeaderRow();
        autoHead.join("idA", "znackaA", "modelA").setHtml("<b>AUTO</b>");
        autoMain.setExpandRatio(autoGrid, 0.5F);
        layout.addComponents(autoMain);
        updateAutoList();
    }

    public void showMechanikForm() {

        mechanikGrid.setColumns("idM", "jmenoM", "specializaceM");
        VerticalLayout mechanikMain = new VerticalLayout(mechanikGrid, mechanikForm);
        mechanikMain.setSizeFull();
        HeaderRow mechanikHead = mechanikGrid.prependHeaderRow();
        mechanikHead.join("idM", "jmenoM", "specializaceM").setHtml("<b>MECHANIK</b>");
        mechanikMain.setExpandRatio(mechanikGrid, 0.5F);
        layout.addComponents(mechanikMain);
        updateMechanikList();
    }

    public void showOpravaForm() {

        opravaGrid.setColumns("idO", "cenaO", "diagnostikaO", "idA", "idM");
        VerticalLayout opravaMain = new VerticalLayout(opravaGrid, opravaForm);
        opravaMain.setSizeFull();
        HeaderRow opravaHead = opravaGrid.prependHeaderRow();
        opravaHead.join("idO", "cenaO", "diagnostikaO", "idA", "idM").setHtml("<b>OPRAVA</b>");
        opravaMain.setExpandRatio(opravaGrid, 0.5F);
        layout.addComponents(opravaMain);
        updateOpravaList();
    }

    public void updateAutoList() {
        AutoS autoS = autoClient.findAllAutoS_JSON(AutoS.class);
        autoGrid.setItems(autoS.getAutoS());
    }

    public void updateMechanikList() {
        MechanikS mechanikS = mechanikClient.findAllMechanikS_JSON(MechanikS.class);
        mechanikGrid.setItems(mechanikS.getMechanikS());
    }

    public void updateOpravaList() {
        OpravaS opravaS = opravaClient.findAllOpravaS_JSON(OpravaS.class);
        opravaGrid.setItems(opravaS.getOpravaS());
    }

    @WebServlet(urlPatterns = "/*", name = "MyUIServlet", asyncSupported = true)
    @VaadinServletConfiguration(ui = MyUI.class, productionMode = false)
    public static class MyUIServlet extends VaadinServlet {
    }
}
